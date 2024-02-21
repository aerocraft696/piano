import cv2

# 读取图像
img = cv2.imread("/home/csoft/luyao/projects/merging_picture/piano_picture/1.jpg")

# 检查图像是否成功加载
if img is None:
    print("Could not open or find the image.")
else:
    # 创建窗口并显示图像
    cv2.imshow("Image", img)

    # 等待用户按下键盘上的任意键
    cv2.waitKey(0)
    cv2.destroyAllWindows()
