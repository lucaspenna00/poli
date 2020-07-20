from keras.preprocessing.image import img_to_array
from keras.models import load_model
import numpy as np
import cv2
import cv_bridge
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import gi

cap = cv2.VideoCapture(0)

MODEL_PATH = "dronecrashednotcrashed.model"

# load the model
print("[INFO] loading model...")
model = load_model(MODEL_PATH)
'''
class MAVCrashed:

    def __init__(self):

        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/bebop/image_raw", Image, self.image_callback)

    def image_callback(self, image):

        try:
            self.cv_image = self.bridge.imgmsg_to_cv2(image, "mono8")
            self.detect_crashed_mav()

        except CvBridgeError as e:
            print(e)


    def detect_crashed_mav(self):

        cv2.imshow("BEBOP CAMERA", self.cv_image)

        self.cv_image = cv2.resize(self.cv_image, (28, 28))
        self.cv_image = self.cv_image.astype("float") / 255.0
        self.cv_image = img_to_array(self.cv_image)
        self.cv_image = np.expand_dims(self.cv_image, axis=0)
        (notCrashed, crashed) = model.predict(image)[0]
        label = "Not Crashed"
        proba = dronecrashednotcrashed

        if crashed > notCrashed:
            label = "Crashed"
            proba = crashed

        label = "{}: {:.2f}%".format(label, proba * 100 )
        frame = cv2.putText(frame, label, (10, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
        cv2.imshow('frame', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
'''
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    image = cv2.resize(frame, (28, 28))
    image = image.astype("float") / 255.0
    image = img_to_array(image)
    image = np.expand_dims(image, axis=0)

    (notCrashed, crashed) = model.predict(image)[0]
    label = 'Not Crashed'
    proba = notCrashed

    if crashed > notCrashed:

        label = "Crashed"
        proba = crashed

    # Display the resulting frame
    label = "{}: {:.2f}%".format(label, proba * 100 )
    frame = cv2.putText(frame, label, (10, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

    cv2.imshow('frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
