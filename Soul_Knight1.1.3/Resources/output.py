import cv2
input_img=cv2.imread("blue.bmp")
for i in range(1,15):
    img=cv2.resize(input_img,(i*10,16),cv2.INTER_CUBIC)
    cv2.imwrite(f"mana_{i}.bmp",img)
