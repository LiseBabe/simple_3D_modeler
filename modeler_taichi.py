import build.main_modeler as main_modeler
import taichi as ti
import taichi.math as tm
import math as m
import numpy as np

from sys import platform

use_tk = True
if platform == "darwin":
    use_tk = False

if use_tk:
    from tkinter import filedialog
    from tkinter import colorchooser
    from tkinter import simpledialog

import wx

app = wx.App(None)

def get_path(wildcard):
    global app
    #app = wx.App(None)
    style = wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
    dialog = wx.FileDialog(None, 'Open', wildcard=wildcard, style=style)
    if dialog.ShowModal() == wx.ID_OK:
        path = dialog.GetPath()
    else:
        path = None
    dialog.Destroy()
    return path

ti.init(arch=ti.gpu)
n = 400
m = 225


pixels = np.ndarray((n,m,3), dtype='f')

modeler1 = main_modeler.modeler()
modeler1.initializedWorld()

gui = ti.ui.Window("Modeler", res=(4*n, 4*m),vsync=True)
gui2 = gui.get_gui()
canvas = gui.get_canvas()

list_selected_id = [-1]
hovered_id = -1
origin = (-1,-1)
selected_id_past = -1
 
old_pos = (0, 0)

while gui.running:
    #gui.get_event()
    pos = gui.get_cursor_pos()

    hovered_id = modeler1.detect(int(pos[0]*n),int((1-pos[1])*m))

    mouse_clicked = False
   
#modeler1.select(hovered_id)
    if gui.get_event(ti.ui.PRESS) :
        if gui.event.key == ti.GUI.LMB :
            mouse_clicked = True
            if hovered_id == -1 :
                for id in list_selected_id:
                    print(id)
                    modeler1.unselect(id)
                list_selected_id = [-1]
            elif gui.is_pressed('Control') and list_selected_id[0] != -1 :
                if hovered_id not in list_selected_id :
                    list_selected_id.append(hovered_id)
            else : 
                for id in list_selected_id:
                    modeler1.unselect(id)
                list_selected_id = [hovered_id]
        
    for id in list_selected_id:
        modeler1.select(id)        

    if mouse_clicked :
        if list_selected_id[0] != -1 :
            if gui.is_pressed('q'):
                modeler1.add(int(pos[0]*n),int((1-pos[1])*m))

            elif not gui.is_pressed('r'):
                    origin = (pos[0],pos[1])
                    print(origin)
                # elif list_selected_id[0] != -1 :
                #     ray = ((pos[0]-origin[0])**2+(pos[1]-origin[1])**2)**(1/2)*4
                #     modeler1.increaseRadius(list_selected_id[0],-(origin[0]-pos[0])/n*100)
        else :
            if gui.is_pressed('q'):
                modeler1.segment_cone(int(pos[0]*n),int((1-pos[1])*m))
        
    
        
    elif gui.is_pressed(ti.GUI.LMB) and gui.is_pressed('c') and list_selected_id[0] != -1:
        if use_tk:
            color = colorchooser.askcolor()
            if color[0] != None:
                for id in list_selected_id:
                    modeler1.changeColor(id, color[0][0], color[0][1], color[0][2])
        else:
            print("Change color - Enter values between 0 and 255")
            try:
                r = int(input("Red: "))
                g = int(input("Green: "))
                b = int(input("Blue: "))

                if (r in range(0, 256) and g in range(0, 256) and b in range(0, 256)):
                    for id in list_selected_id:
                        modeler1.changeColor(id, r,g,b)
                else:
                    print("Value incorrect")
            except:
                print("Value incorrect")
        
    elif gui.is_pressed('d') :
        for id in list_selected_id:
            modeler1.delete(id)
        list_selected_id = [-1]

    elif gui.is_pressed('f') :
        modeler1.addLink(list_selected_id[0],list_selected_id[1])

    elif gui.is_pressed(ti.GUI.LMB) and gui.is_pressed('r') and list_selected_id[0] != -1:
        # print(origin)
        # for i in list_selected_id:
        #     modeler1.increaseRadius(i,-(origin[0]-pos[0])/n*100)
        # ray = ((pos[0]-origin[0])**2+(pos[1]-origin[1])**2)**(1/2)*4
        # modeler1.increaseRadius(list_selected_id[0],-(origin[0]-pos[0])/n*100)

        if use_tk :
            title = "Radius"    
            prompt = "Enter the radius of the circle: "
            radius = simpledialog.askfloat(title, prompt)
            for id in list_selected_id:
                modeler1.changeRadius(id, radius)
        else : 
            print("Change radius - Enter values between 0 and 1")
            try:
                radius = float(input("Radius: "))
                if 0 < radius and radius < 10:
                    for id in list_selected_id:
                        modeler1.changeRadius(id, radius)
                else:
                    print("Value incorrect")
            except:
                print("Value incorrect")

    elif gui.get_event(ti.ui.RELEASE):
        if gui.event.key == 'r':
            origin = (-1,-1)

    elif gui.is_pressed(ti.GUI.LMB) and not gui.is_pressed('q') and not gui.is_pressed('r') and list_selected_id[0] != -1: 
        for id in list_selected_id:
            modeler1.move_sphere(id, old_pos[0], old_pos[1], int(pos[0]*n), int((1-pos[1])*m))
        #modeler1.move_sphere(list_selected_id, old_pos[0], old_pos[1], int(pos[0]*n), int((1-pos[1])*m))


    #rotate the camera around a fixed point
    if gui.is_pressed(ti.GUI.LEFT) :
        if gui.is_pressed(ti.GUI.CTRL) :
            modeler1.move_camera_sideways(-0.05, 0.0)
        else:
            modeler1.rotate_camera(-0.1,0)
    elif gui.is_pressed(ti.GUI.RIGHT) :
        if gui.is_pressed(ti.GUI.CTRL) :
            modeler1.move_camera_sideways(0.05, 0.0)
        else:
            modeler1.rotate_camera(0.1,0)
    elif gui.is_pressed(ti.GUI.UP) :
        if gui.is_pressed(ti.GUI.SHIFT) :
            modeler1.move_camera_forward(0.1)
        elif gui.is_pressed(ti.GUI.CTRL) :
            modeler1.move_camera_sideways(0.0, -0.05)
        else : 
            modeler1.rotate_camera(0,0.1)
    elif gui.is_pressed(ti.GUI.DOWN) :
        if gui.is_pressed(ti.GUI.SHIFT) :
            modeler1.move_camera_forward(-0.1)
        elif gui.is_pressed(ti.GUI.CTRL) :
            modeler1.move_camera_sideways(0.0, 0.05)
        else : 
            modeler1.rotate_camera(0,-0.1)
    #save and load functions
    elif gui.is_pressed(ti.GUI.SHIFT) :
        if gui.is_pressed('s') :
            if use_tk:
                filename = filedialog.asksaveasfilename()
            else:
                filename = input("Save - Enter filename: ")
            if filename != '':
                modeler1.save(filename)
        elif gui.is_pressed('l') :
            if use_tk:
                filename = filedialog.askopenfilename()
            else:
                filename = input("Open - Enter filename: ")
            if filename != '':
                modeler1.load(filename)

    old_pos = (int(pos[0]*n),int((1-pos[1])*m))
    
    modeler1.computeImageSpan(pixels)
    canvas.set_image(pixels)

    gui.show()