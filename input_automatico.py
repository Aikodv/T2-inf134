import pyautogui
import time

time.sleep(5)

patrones_completos = ["1","XXX","OO_","___","1","XOX","OX_","OXO","2","XXX","___","OO_","2","XOX","OX_","OXO","1","XOX","OX_","OXO","2","XOX","OX_","OXO","3",]

for mensaje in patrones_completos:
    pyautogui.typewrite(mensaje, interval=0.1)
    pyautogui.press('enter')
    print("Línea leída:", mensaje)