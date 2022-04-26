from numpy import Infinity


activities = []
ACT_NUM = 0
START_TIME = 1
END_TIME = 2

def parsetext():
    global activities
    file = open("act.txt", "r")
    while 1:
        line = file.readline()

        if line == "": # if we have reached EOF
            break
        else:
            numActs = int(line)

        act = [(0, 0, 0)] * numActs

        # Parses each line in this activity set
        for i in range(numActs):
            line = file.readline()
            idx = 0

            # Parses the line for this activity
            for j in range(len(act[i])):
                num_str = ""

                #Parses this current number
                while 1:
                    if not line[idx].isdigit():
                        idx += 1
                        break
                    else:
                        num_str += line[idx]
                        idx += 1
                temp = list(act[i])
                temp[j] = int(num_str)
                act[i] = tuple(temp) # stupid but this is how you set tuples

        activities.append(act) # Appends to activities
    file.close()


# Used the Insertion Sort code by Geeks4Geeks as reference
# for this function.
def sortactivities(list):
    for i in range(1, len(list)):
        current = list[i]

        j = i-1
        while j >= 0 and current[START_TIME] > list[j][START_TIME]:
            list[j+1] = list[j]
            j -= 1
        list[j+1] = current

    print(list)
    return list



def main():
    parsetext()

    for i in range(len(activities)):
        activities[i] = sortactivities(activities[i])

if __name__ == "__main__":
    main()