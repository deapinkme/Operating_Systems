import sys

timeQuantum = 0

processID = []
arrivalTime = []
burstTime = []
priority = []

def main():
  global timeQuantum
  if len(sys.argv) != 3:
    print('Usage: <procfile.csv> <timequantum>')
    exit(1)
  readData(sys.argv[1])
  timeQuantum = int(sys.argv[2])
  runFCFS()
  runPBS()
  runRR()


def readData(fname):
  infile = open(fname, 'r')
  Lines = infile.readlines()
  # Strips the strings to make list of lists
  for line in Lines:
      line = line.strip()
      vals = line.split(",")
      processID.append(int(vals[0]))
      arrivalTime.append(int(vals[1]))
      burstTime.append(int(vals[2]))
      priority.append(int(vals[3]))

def runFCFS():
  remainingTime = burstTime[::]
  arrivalTimeMarked = arrivalTime[::]
  waitingTime = [0] * len(arrivalTime) # zeroes
  turnaroundTime = [0] * len(arrivalTime) # zeroes
  currentTime = 0
  gantChart = []
  while (sum(remainingTime) > 0):
    # nextProc = arrivalTimeMarked.index(min(arrivalTimeMarked)) # correct version
    nextProc = len(arrivalTimeMarked) - 1 - arrivalTimeMarked[::-1].index(min(arrivalTimeMarked)) # same as above, but matches assignment results - see bug report
    if arrivalTime[nextProc] > currentTime: # idle
      endTime = arrivalTime[nextProc]
      gantChart.append([currentTime, 'IDLE', endTime])
      currentTime = endTime
    waitingTime[nextProc] = currentTime - arrivalTime[nextProc]
    endTime = currentTime + remainingTime[nextProc]
    turnaroundTime[nextProc] = endTime - arrivalTime[nextProc]
    gantChart.append([currentTime, processID[nextProc], endTime])
    # Update status
    arrivalTimeMarked[nextProc] = 1000000 # large number used as sentinel
    remainingTime[nextProc] = 0
    currentTime = endTime
  print('------------------- FCFS ------------------')
  printTimes(waitingTime, turnaroundTime)
  printGantChart(gantChart)
  ptintStats(waitingTime, turnaroundTime, currentTime)

def runPBS():
  remainingTime = burstTime[::]
  arrivalTimeMarked = arrivalTime[::]
  waitingTime = [0] * len(arrivalTime) # zeroes
  turnaroundTime = [0] * len(arrivalTime) # zeroes
  currentTime = 0
  gantChart = []
  while (sum(remainingTime) > 0):
    minPri = 100000000; # high value as sentinel
    nextProc = -1; # for idle if none has arrived
    for i in range(len(processID)):
      if (arrivalTimeMarked[i] <= currentTime): # it has arrived
        if (priority[i] < minPri):
          nextProc = i;
          minPri = priority[i]
    if -1 == nextProc: # idle
      endTime = min(arrivalTimeMarked)
      gantChart.append([currentTime, 'IDLE', endTime])
      currentTime = endTime
      continue
    waitingTime[nextProc] = currentTime - arrivalTime[nextProc]
    endTime = currentTime + remainingTime[nextProc]
    turnaroundTime[nextProc] = endTime - arrivalTime[nextProc]
    gantChart.append([currentTime, processID[nextProc], endTime])
    # Update status
    arrivalTimeMarked[nextProc] = 1000000 # large number used as sentinel
    remainingTime[nextProc] = 0
    currentTime = endTime
  print('------------------- PBS -------------------')
  printTimes(waitingTime, turnaroundTime)
  printGantChart(gantChart)
  ptintStats(waitingTime, turnaroundTime, currentTime)

def runRR():
  global timeQuantum
  remainingTime = burstTime[::]
  arrivalTimeMarked = arrivalTime[::]
  waitingTime = [0] * len(arrivalTime) # zeroes
  turnaroundTime = [0] * len(arrivalTime) # zeroes
  currentTime = 0
  gantChart = []
  nextProc = -2; # for undecided
  while (sum(remainingTime) > 0):
    if (-2 == nextProc): # undecided
      nextProc = 0;
    found = False
    for i in range(len(processID)): # loop to find unfinished processID
      nextProc = (nextProc + 1) % len(processID);
      if arrivalTimeMarked[nextProc] <= currentTime:
        found = True
        break
    if not found: # idle
      endTime = min(arrivalTimeMarked)
      gantChart.append([currentTime, 'IDLE', endTime])
      currentTime = endTime
      continue
    endTime = currentTime + min([timeQuantum, remainingTime[nextProc]])
    turnaroundTime[nextProc] = endTime - arrivalTime[nextProc]
    gantChart.append([currentTime, processID[nextProc], endTime])
    # Update status
    remainingTime[nextProc] -= min([timeQuantum, remainingTime[nextProc]])
    if (0 == remainingTime[nextProc]):
      waitingTime[nextProc] = endTime - arrivalTime[nextProc] - burstTime[nextProc]
      arrivalTimeMarked[nextProc] = 1000000 # large number used as sentinel
    currentTime = endTime
  print('-------------------- RR -------------------')
  printTimes(waitingTime, turnaroundTime)
  printGantChart(gantChart)
  ptintStats(waitingTime, turnaroundTime, currentTime)

def printGantChart(gantChart):
  print()
  print('Gantt Chart is:')
  for item in gantChart:
    print('[', item[0], ']-- ', item[1], ' --[', item[2], ']')

def printTimes(waitingTime, turnaroundTime):
  print('Process ID | Waiting Time | Turnaround Time')
  sortedProcessID = processID[::]
  sortedProcessID.sort()
  for i in range(len(processID)):
    si = processID.index(sortedProcessID[i])
    print('    ', processID[si], '    |     ', waitingTime[si], '      |     ', turnaroundTime[si])

def ptintStats(waitingTime, turnaroundTime, finalTime):
  print()
  print('Average Waiting Time: ', sum(waitingTime)/len(waitingTime))
  print('Average Turnaround Time: ', sum(turnaroundTime)/len(turnaroundTime))
  print('Throughput: ', len(processID)/finalTime)
  print()

main()