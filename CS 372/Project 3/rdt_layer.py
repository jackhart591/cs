from segment import Segment


# #################################################################################################################### #
# RDTLayer                                                                                                             #
#                                                                                                                      #
# Description:                                                                                                         #
# The reliable data transfer (RDT) layer is used as a communication layer to resolve issues over an unreliable         #
# channel.                                                                                                             #
#                                                                                                                      #
#                                                                                                                      #
# Notes:                                                                                                               #
# This file is meant to be changed.                                                                                    #
#                                                                                                                      #
#                                                                                                                      #
# #################################################################################################################### #


class RDTLayer(object):
    # ################################################################################################################ #
    # Class Scope Variables                                                                                            #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    DATA_LENGTH = 4 # in characters                     # The length of the string data that will be sent per packet...
    FLOW_CONTROL_WIN_SIZE = 15 # in characters          # Receive window size for flow-control
    sendChannel = None
    receiveChannel = None
    dataToSend = ''
    currentIteration = 0                                # Use this for segment 'timeouts'

    # ################################################################################################################ #
    # __init__()                                                                                                       #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def __init__(self):
        self.sendChannel = None
        self.receiveChannel = None
        self.dataToSend = ''
        self.currentIteration = 0
        self.remainingFCW = RDTLayer.FLOW_CONTROL_WIN_SIZE
        self.charsSent = 0 # For sequence num purposes
        self.receivedString = "" # Final string

    # ################################################################################################################ #
    # setSendChannel()                                                                                                 #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the unreliable sending lower-layer channel                                                 #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setSendChannel(self, channel):
        self.sendChannel = channel

    # ################################################################################################################ #
    # setReceiveChannel()                                                                                              #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the unreliable receiving lower-layer channel                                               #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setReceiveChannel(self, channel):
        self.receiveChannel = channel

    # ################################################################################################################ #
    # setDataToSend()                                                                                                  #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the string data to send                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setDataToSend(self,data):
        self.dataToSend = data

    # ################################################################################################################ #
    # getDataReceived()                                                                                                #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to get the currently received and buffered string data, in order                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def getDataReceived(self):
        return self.receivedString

    # ################################################################################################################ #
    # processData()                                                                                                    #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # "timeslice". Called by main once per iteration                                                                   #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processData(self):
        self.currentIteration += 1
        self.processReceiveAndSendRespond()
        self.processSend()

    # ################################################################################################################ #
    # processSend()                                                                                                    #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Manages Segment sending tasks                                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processSend(self):
        if self.dataToSend == '':
           return

        currChar = self.charsSent

        # While there is still remaining space in the FCW
        while self.remainingFCW > 0:

            # If there is no more data, stop
            if currChar == len(self.dataToSend):
               break

            segmentSend = Segment()

            # If there's enough for a full packet, send a full packet, else send only how much remains in FCW
            if self.remainingFCW > RDTLayer.DATA_LENGTH:
                sendSize = RDTLayer.DATA_LENGTH
            else:
                sendSize = self.remainingFCW

            data = self.dataToSend[currChar:(currChar + sendSize)]
            sendSize = len(data) # Accounts for the case in which the string is smaller than the intended send size
            seqnumInt = currChar + sendSize

            seqnum = f"{seqnumInt}"

            self.remainingFCW -= sendSize # Update flow control window
            currChar += sendSize


            # ############################################################################################################ #
            # Display sending segment
            segmentSend.setData(seqnum,data)
            print("Sending segment: ", segmentSend.to_string())

            # Use the unreliable sendChannel to send the segment
            self.sendChannel.send(segmentSend)

    # Looks for any missing segments
    def findSeqErrors(self, segList, startPos):
        pos = startPos
        for seg in segList:
            pos += len(seg.payload)
            if pos != int(seg.seqnum):
                print(f"found error: {seg.seqnum}")
                return pos

        return 0 # No missing segments

    # Takes a segment and finds its place in the current list of 
    # Segments (reorders segments)
    def assembleSegments(self, segment, segList):
        foundSpot = False
        for i, elem in enumerate(segList):
            if int(segment.seqnum) < int(elem.seqnum):
                segList.insert(i, segment)
                foundSpot = True
                break
        # if a no larger sequence num was found, put on end because it must be the latest one so far
        if not foundSpot:
            segList.append(segment)

        return segList

    def receiveAcks(self, segment):
        self.remainingFCW += (int(segment.acknum) - self.charsSent)
        self.charsSent = int(segment.acknum)

        # this is not selective retransmission!!

    # ################################################################################################################ #
    # processReceive()                                                                                                 #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Manages Segment receive tasks                                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processReceiveAndSendRespond(self):
        segmentAck = Segment()                  # Segment acknowledging packet(s) received

        # This call returns a list of incoming segments (see Segment class)...
        listIncomingSegments = self.receiveChannel.receive()

        incomingString = ""
        orderedList = []
        lastSeqnum = -1

        # Sort segments received by seqnum
        for seg in listIncomingSegments:
            if seg.seqnum != -1:
                orderedList = self.assembleSegments(seg, orderedList)
            elif seg.acknum != -1:
                self.receiveAcks(seg)
            else:
                return;

        if (len(orderedList) > 0): # If there is data to process
            lastSeqnum = self.findSeqErrors(orderedList, len(self.receivedString)) # Check for sequence errors
            print(f"Last sequence num: {lastSeqnum}")

            if lastSeqnum == 0: # If no sequence errors were found
                for elem in orderedList:
                    incomingString += elem.payload
                lastSeqnum = orderedList[len(orderedList)-1].seqnum # Set seqnum to latest one for acking purposes

            self.receivedString += incomingString

        acknum = f"{lastSeqnum}"

        # ############################################################################################################ #
        # Display response segment
        segmentAck.setAck(acknum)
        print("Sending ack: ", segmentAck.to_string())

        # Use the unreliable sendChannel to send the ack packet
        self.sendChannel.send(segmentAck)
