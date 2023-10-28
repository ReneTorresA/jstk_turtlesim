#!/usr/bin/env python3



import rospy
from std_msgs.msg import Bool
import random
from turtlesim.srv import TeleportAbsolute, TeleportAbsoluteRequest, SetPen,SetPenRequest
# Function when a message is received
def callback(data):

    rospy.wait_for_service('/turtle1/teleport_absolute')
    spawn_client = rospy.ServiceProxy('/turtle1/teleport_absolute',TeleportAbsolute)

    request = TeleportAbsoluteRequest()

    request.x = random.uniform(0,11)
    request.y = random.uniform(0,11)
    request.theta = random.uniform(0,3.1416)


    rospy.wait_for_service('/turtle1/set_pen')
    set_pen_client = rospy.ServiceProxy('/turtle1/set_pen',SetPen)
    requestdos=SetPenRequest()
    requestdos.r = random.randint(0,255) 
    requestdos.g = random.randint(0,255)
    requestdos.b = random.randint(0,255)
    requestdos.width = random.randint(0,10)
    

    if data.data == True:
        spawn_client(request)
        set_pen_client(requestdos)
        rospy.loginfo("La tortuga ha sido movida aleatoriamente")
    else:
        rospy.loginfo(f"Esperando por el servicio")


rospy.init_node('listener_ button') # Create node
rospy.Subscriber('/button1', Bool, callback)   # Create subscriber
rospy.spin()                # Wait for a message