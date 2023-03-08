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
    TIMEOUT_ITERATION = 3
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
        self.lastContigChar = 0 # Last char in our contiguous data
        self.unAckedSegs = []
        self.lastSentChar = 0
        self.countSegmentTimeouts = 0
        self.segList = [] # Contains segments in order

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
        newStr = ""
        for seg in self.segList:
            newStr += seg.payload

        return newStr

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

    def sendSegment(self, segment):
        print("Sending segment: ", segment.to_string())
        self.sendChannel.send(segment)

        if int(self.lastSentChar) < int(segment.seqnum): # If packets are being retransmitted, don't update these
            self.remainingFCW -= len(segment.payload) # Update flow control window
            self.lastSentChar += len(segment.payload)

    def checkForTimeouts(self):
        for segment in self.unAckedSegs:
            if int(segment.seqnum) <= int(self.lastContigChar): # Are there any acked packets?
                print(f"Removing Seqnum: {segment.seqnum}")
                self.unAckedSegs.remove(segment)
                continue

            # Check for any timed out packets and attempt a resend
            if (self.currentIteration - segment.getStartIteration()) >= RDTLayer.TIMEOUT_ITERATION:
                self.countSegmentTimeouts += 1
                
                newSegment = Segment()
                data = self.dataToSend[(int(segment.seqnum) - len(segment.payload)):int(segment.seqnum)] # Get original data
                newSegment.setData(f"{segment.seqnum}", data)
                segment = newSegment

                segment.setStartIteration(self.currentIteration)
                self.sendSegment(segment)

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

        self.checkForTimeouts()

        currChar = self.lastSentChar 
        
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
            seqnumInt = currChar + len(data)
            currChar += len(data)

            # ############################################################################################################ #
            # Display sending segment
            segmentSend.setData(f"{seqnumInt}", data)
            segmentSend.setStartIteration(self.currentIteration)
            self.unAckedSegs.append(segmentSend)

            # Use the unreliable sendChannel to send the segment
            self.sendSegment(segmentSend)

    # Looks for any errors in seqnums or checksum
    def findErrors(self):
        pos = 0
        for seg in self.segList:
            if (pos + len(seg.payload)) != int(seg.seqnum):
                return pos
            elif not seg.checkChecksum():
                print("Found checksum error")
                return pos
            else:
                pos += len(seg.payload)

        return self.segList[len(self.segList)-1].seqnum # No missing segments

    # Takes a segment and finds its place in the current list of 
    # Segments (reorders segments)
    def insertSegment(self, segment):
        foundSpot = False
        for i, elem in enumerate(self.segList):
            if int(segment.seqnum) == int(elem.seqnum): # Don't reinsert a copy
                foundSpot = True
                self.segList.remove(elem)
                self.segList.insert(i, segment)
                break
            if int(segment.seqnum) < int(elem.seqnum): # Find first seqnum that is larger
                self.segList.insert(i, segment)
                foundSpot = True
                break
        # if a no larger sequence num was found, put on end because it must be the latest one so far
        if not foundSpot:
            self.segList.append(segment)

    def receiveAcks(self, segment):
        if segment.acknum != "-1":
            self.remainingFCW += (int(segment.acknum) - self.lastContigChar)
            self.lastContigChar = int(segment.acknum)

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
        lastSeqnum = -1

        # Sort segments received by seqnum
        for seg in listIncomingSegments:
            if seg.seqnum != -1:
                self.insertSegment(seg)
            elif seg.acknum != -1:
                self.receiveAcks(seg)
            else:
                return

        if (len(self.segList) > 0): # If there is data to process
            lastSeqnum = self.findErrors() # Check for sequence errors

        acknum = f"{lastSeqnum}"

        # ############################################################################################################ #
        # Display response segment
        segmentAck.setAck(acknum)
        print("Sending ack: ", segmentAck.to_string())

        # Use the unreliable sendChannel to send the ack packet
        self.sendChannel.send(segmentAck)
