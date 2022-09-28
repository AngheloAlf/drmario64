#!/usr/bin/env python3

import argparse
from jenkinsapi.jenkins import Jenkins, Job
import requests
import time

def getServerInstance(username, password) -> Jenkins:
    print("Getting server instance...")
    jenkins_url = 'https://jenkins.deco.mp/'
    jenkinsServer = Jenkins(jenkins_url, username=username, password=password, useCrumb=True)
    print(jenkinsServer)
    print()
    return jenkinsServer

def printJobs(jenkinsServer: Jenkins, project: str):
    jobList = jenkinsServer.get_jobs_list()
    #for x in jenkinsServer.get_jobs_info():
    #    print(x)
    for jobName in filter(lambda x: x.startswith(f"{project}/"), jobList):
        jobInstance = jenkinsServer.get_job(jobName)
        print('Job Name:%s' % (jobInstance.name))
        # print('Job Description:%s' % (jobInstance.get_description()))
        print('Is Job running:%s' % (jobInstance.is_running()))
        print('Is Job enabled:%s' % (jobInstance.is_enabled()))
        print('Build id:%s' % (next(jobInstance.get_build_ids())))
        print()

def abortQueue(jenkinsServer: Jenkins, project: str):
    print("Starting abort routine")
    jenkinsQueue = jenkinsServer.get_queue()
    # jenkinsQueue.pprint()

    removedElements = 0
    for queueId, queueItem in jenkinsQueue.iteritems():
        if queueItem.why is None:
            break
        # Filter out stuff only from this project
        if project.lower() in queueItem.why.lower():
            #queueItem.pprint()
            #print(queueItem.name)
            #print(queueId)
            print(f"Element: {removedElements}; queueId: {queueId}")
            #queueJob.pprint()
            #print()
            jenkinsQueue.delete_item_by_id(queueId)
            removedElements += 1
    print(f"Removed elements: {removedElements}")

    print()

def isJobOk(prJob: Job) -> bool:
    lastFailed = prJob.get_last_failed_buildnumber()
    lastGood = prJob.get_last_good_buildnumber()
    #lastStable = prJob.get_last_stable_buildnumber()
    lastCompleted = prJob.get_last_completed_buildnumber()

    #print("Last failed build:", lastFailed)
    #print("Last good build:", lastGood)
    #print("Last stable build:", lastStable)
    #print("Last completed build:", lastCompleted)
    #print("Equals? ", lastFailed == lastGood)
    if (lastFailed == lastGood or lastGood != lastCompleted):
        return False
    return True


def fixMasterBuild(jenkinsServer: Jenkins, project: str):
    print("Checking master...")
    prJob = jenkinsServer.get_job(f"{project}/master")
    #prJob.pprint()

    if not isJobOk(prJob) and not prJob.is_queued_or_running():
        print("Last master build doesn't look OK. Let's add it to the queue again...")
        prJob.invoke()
    else:
        print("Everything good with master!")

    print()

reposMap = {
    "MM": "zeldaret/mm",
    "OOT": "zeldaret/oot",
    "Paper Mario": "pmret/papermario",
    "TMC": "zeldaret/tmc",
    "ZAPD": "zeldaret/ZAPD",
}

def addToQueueByLabel(jenkinsServer: Jenkins, project: str, label: str):
    print("Getting merge-ready PRs from Github...")
    response = requests.get(f"https://api.github.com/search/issues?q=is:open%20is:pr%20label%3A{label}%20repo:{reposMap[project]}")
    if response.status_code == 200 and 'application/json' in response.headers.get('Content-Type',''):
        responseJson = response.json()
        print(f"Found {responseJson['total_count']} PRs")

        for pr in responseJson["items"]:
            prNumber = pr["number"]
            #print(prNumber)
            prJob = jenkinsServer.get_job(f"{project}/PR-{prNumber}")
            #prJob.pprint()
            if prJob.is_queued_or_running():
                print(f"{prJob.name} is already in the queue. Skiping...")
                continue

            print(f"Adding {prJob.name} to the queue... ", end="")
            prJob.invoke()
            print("Done!")
    else:
        print("Something bad happened!")
        exit(-1)

    print()

def addEverythingToQueue(jenkinsServer: Jenkins, project: str):
    print("Adding everything to the queue again...")

    jobList = jenkinsServer.get_jobs_list()

    i = 0
    for jobName in filter(lambda x: x.startswith(f"{project}/"), jobList):
        prJob = jenkinsServer.get_job(jobName)
        isPROk = False
        try:
            isPROk = isJobOk(prJob)
        except:
            pass
        if not isPROk and not prJob.is_queued_or_running():
            print(f"{i}: {prJob.name} doesn't look OK. Let's add it to the queue again...")
            prJob.invoke()
        else:
            print(f"{i}: Everything good with {prJob.name}, skiping...")
        i += 1

    print()

def jenkinsMain():
    # TODO
    description = ""
    # TODO
    epilog = """\
    """

    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("username", help="Your Jenkins username")
    parser.add_argument("password", help="Your Jenkins password")
    parser.add_argument("--project", help="Select the project to use", default="MM", choices=["MM", "OOT", "Paper Mario", "TMC", "ZAPD"])
    parser.add_argument("--mode", help="""Chooses the mode to run. 
    `all` runs the modes `abort`, `master` and `label` in that order.. 
    `abort` aborts every PR in the queue.
    `master` performs a sanity check on the master branch and re-builds it if necessary
    `label` adds every PR to the queue with the label passed with --label.
    `add-everything` adds every PR.
    It should be noted that PRs which are already building OK will not be re-added to the queue.""", choices=["all", "abort", "master", "label", "add-everything"], required=True)
    parser.add_argument("--label", help="The label to use as a filter when using `label` mode. Defaults to `merge-ready`", default="merge-ready")
    args = parser.parse_args()

    startTime = time.time()

    jenkinsServer = getServerInstance(args.username, args.password)

    #printJobs(jenkinsServer, args.project)

    if args.mode in ("all", "abort",):
        abortQueue(jenkinsServer, args.project)
    if args.mode in ("all", "master",):
        fixMasterBuild(jenkinsServer, args.project)
    if args.mode in ("all", "label",):
        addToQueueByLabel(jenkinsServer, args.project, args.label)
    if args.mode in ("add-everything",):
        addEverythingToQueue(jenkinsServer, args.project)

    print("Everything done!")

    endTime = time.time()

    print(f"Elapsed time: {endTime-startTime:.3f} seconds")


if __name__ == '__main__':
    jenkinsMain()
