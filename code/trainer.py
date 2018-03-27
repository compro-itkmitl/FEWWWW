import cv2
import os
import numpy as np
from PIL import Image

'''create recognizer'''
rec = cv2.face.LBPHFaceRecognizer_create()

'''This is path go to dataset'''
path = 'user'

'''define function get img'''
def getimg(path):
	'''get image path and append to list imgpath'''
	imgpath = [os.path.join(path, f) for f in os.listdir(path)]

	'''create list of faces and Id'''
	faces, Id = [], []

	'''loop for in img path'''
	for p in imgpath:
		'''add img to face_img and connvert to grayscale'''
		face_img = Image.open(p).convert('L')
		
		face_np = np.array(face_img, 'uint8')
		Ids = int(os.path.split(p)[-1].split('.')[0][-1])
		faces.append(face_np)
		
		print(Ids)
		
		Id.append(Ids)
		
		cv2.imshow("train", face_np)
		cv2.waitKey(10)
	
	return Id, faces

Id, faces = getimg(path)

rec.train(faces, np.array(Id))
rec.save('trainingdata.yml')
cv2.destroyAllWindows()
