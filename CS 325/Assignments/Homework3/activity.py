from numpy import Infinity

# Name: Jackson Hart
# Date: 4/27/2022
# Class: CS 325

activities = []
ACT_NUM = 0
START_TIME = 1
END_TIME = 2

def parseset(set):
    idx = 0
    activity = (0, 0, 0)

    # Parses the line for this activity
    for j in range(3):
        num_str = ""

        #Parses this current number
        while 1:
            if not set[idx].isdigit():
                idx += 1
                break
            else:
                num_str += set[idx]
                idx += 1
        temp = list(activity)
        temp[j] = int(num_str)
        activity = tuple(temp) # stupid but this is how you set tuples

    return activity

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
            act[i] = parseset(line)

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

    return list



def main():
    parsetext()

    # Sort each set by latest start time
    for i in range(len(activities)):
        activities[i] = sortactivities(activities[i])

    i = 1
    for activity_set in activities:
        print(f"Set {i}")
        activity_list = []
        j = 0
        for act in activity_set:
            if (len(activity_list) == 0): # always take the latest starting activity
                activity_list.append(act)

            # If this activity starts before or at the time the last activity ends
            elif(activity_list[j][START_TIME] >= act[END_TIME]):
                activity_list.append(act)
                j += 1

        print(f"Maximum number of activities = {len(activity_list)}")

        for k in range(len(activity_list)):  
            #print them in reverse order to get it to look like the solution file
            print(f" {activity_list[(len(activity_list) - k) - 1][ACT_NUM]}", end=" ")

        print()   
        print()     
        i += 1

    

if __name__ == "__main__":
    main()