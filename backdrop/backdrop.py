#import sys
#import time
import win32gui, win32con, win32api
background = win32api.RGB(1, 1, 1) #black and white are in use by win32
select_limit = 999999999 #usually about 1000
select_default = 0 #0 Program Manager
select_counter = 0
select_window = 0

app_name = "Backdrop"
app_icon_path = "shell32.dll"
app_icon_id = -22 #107

systray_name = app_name + " Systray"
systray_icon_path = app_icon_path
systray_icon_id = app_icon_id

submenu_exit = "Exit " + app_name
submenu_exit_affirm = "Affirm " + submenu_exit
submenu_prev = "Previous " + app_name
submenu_next = "Next " + app_name
submenu_show = "Show " + app_name
submenu_hide = "Hide " + app_name
submenu_reset = "Reset " + app_name

WM_SYSTRAY             = win32con.WM_APP + 0
WM_SUBMENU             = WM_SYSTRAY + 1

WM_SUBMENU_EXIT        = WM_SUBMENU + 1
WM_SUBMENU_EXIT_AFFIRM = WM_SUBMENU + 2
WM_SUBMENU_PREV        = WM_SUBMENU + 3
WM_SUBMENU_NEXT        = WM_SUBMENU + 4
WM_SUBMENU_HIDE        = WM_SUBMENU + 5
WM_SUBMENU_SHOW        = WM_SUBMENU + 6
WM_SUBMENU_RESET       = WM_SUBMENU + 7

hInstance = 0
hSystray = None
hWindow = None
hCapture = None
running = True
ready = False

def app():
    global running, ready, select_window
    systray(systray_name)
    window(app_name)
    while True:
        try:
            process()
        except Exception as error:
            print(error)
        if running == False:
            window_remove()
            systray_remove()
            ready = False
            break
        elif ready == True:
            pass
            #time.sleep(1)
            #select_window += 1
            #window_refresh()
    #print("app_exit")

def enumProc(hWnd, select):
    global hCapture, select_counter, select_window
    if select_counter >= select:
        return False # None
    if select_counter >= select_limit:
        return False # None
    hCapture = win32gui.GetWindow(hWnd, win32con.GW_HWNDNEXT)
    select_counter += 1
    return True

def wndProc(hWnd, message, wParam, lParam):
    global running, ready, hWindow, hCapture, select_counter, select_window
    #print(hex(message))
    if message == win32con.WM_PAINT:
        hdc, ps = win32gui.BeginPaint(hWnd)
        #"""
        hCapture = win32gui.GetWindow(hWnd, win32con.GW_HWNDLAST)
        try:
            ready = True
            select_counter = 0
            win32gui.EnumWindows(enumProc, select_window)
        except:
            print(select_counter, win32gui.GetWindowText(hCapture))
            pass
        hdcCapture = win32gui.GetWindowDC(hCapture)
        source = win32gui.GetClientRect(hCapture)
        viewport = win32gui.GetClientRect(hWnd)
        brush =  win32gui.CreateSolidBrush(background) #!!!
        win32gui.FillRect(hdc, viewport, brush) #!!!
        #"""
        #"""
        source_width = source[2] - source[0] #source.right - source.left
        source_height = source[3] - source[1] #source.bottom - source.top
        viewport_width = viewport[2] - viewport[0] #viewport.right - viewport.left
        viewport_height = viewport[3] - viewport[1] #viewport.bottom - viewport.top
        win32gui.SetStretchBltMode(hdc, win32con.HALFTONE)
        win32gui.SetStretchBltMode(hdcCapture, win32con.HALFTONE)
        win32gui.StretchBlt(hdc, 0, 0, viewport_width, viewport_height,
                            hdcCapture, 0, 0, source_width, source_height,
                            win32con.SRCCOPY)
        #"""
        win32gui.ReleaseDC(hWnd, hdcCapture)
        win32gui.EndPaint(hWnd, ps)
    elif message == win32con.WM_MOUSEWHEEL:
        #print("mousewheel")
        return win32gui.DefWindowProc(hWnd, message, wParam, lParam)
    elif message == WM_SYSTRAY:
        if lParam == win32con.WM_MOUSEMOVE:
            #print("WM_SYSTRAY_MOUSEMOVE")
            pass
        elif lParam == win32con.WM_LBUTTONDOWN:
            #print("WM_SYSTRAY_LBUTTONDOWN")
            window(app_name)
        elif lParam == win32con.WM_LBUTTONUP:
            #print("WM_SYSTRAY_LBUTTONUP")
            pass
        elif lParam == win32con.WM_RBUTTONDOWN:
            #print("WM_SYSTRAY_RBUTTONDOWN")
            submenu_systray(hWnd)
        elif lParam == win32con.WM_RBUTTONUP:
            #print("WM_SYSTRAY_RBUTTONUP")
            pass
        elif lParam == win32con.WM_MBUTTONDOWN:
            #print("WM_SYSTRAY_MBUTTONDOWN")
            pass
        elif lParam == win32con.WM_MBUTTONUP:
            #print("WM_SYSTRAY_MBUTTONUP")
            pass
        else: # Unhandled Mouse Scroll Message and Peripheral Message
            #print("WM_SYSTRAY_UNKNOWN")
            pass
        return win32gui.DefWindowProc(hWnd, message, wParam, lParam)
    elif message == win32con.WM_COMMAND:
        cmd = win32api.LOWORD(wParam)
        #print("command_msg", cmd)
        if cmd == WM_SUBMENU_EXIT:
            submenu(hWnd, [submenu_exit_affirm], [WM_SUBMENU_EXIT_AFFIRM])
        elif cmd == WM_SUBMENU_EXIT_AFFIRM:
            running = False
        elif cmd == WM_SUBMENU_PREV:
            #print("previous")
            if select_window > 0:
                select_window -= 1
        elif cmd == WM_SUBMENU_NEXT:
            #print("next")
            if select_window < select_limit:
                select_window += 1
        elif cmd == WM_SUBMENU_SHOW:
            window(app_name)
        elif cmd == WM_SUBMENU_HIDE:
            window_remove()
        elif cmd == WM_SUBMENU_RESET:
            #print("reset")
            select_window = select_default
        #win32gui.InvalidateRect(hWnd, None, True)
        #win32gui.PostMessage(hWnd, win32con.WM_PAINT, 0, 0)
        #win32gui.InvalidateRect(hWindow, None, True)
        window_refresh()
    elif message == win32con.WM_DESTROY:
        #print("destroy_msg")
        pass
    elif message == win32con.WM_CLOSE:
        #print("close_msg")
        window_remove()
    else:
        #print(message)
        return win32gui.DefWindowProc(hWnd, message, wParam, lParam)
    return 0 #1

def submenu(hWnd, options, signals):
    wSystraySubmenu = win32gui.CreatePopupMenu()
    for i in range(0, len(options)):
        win32gui.AppendMenu(wSystraySubmenu, win32con.MF_STRING, signals[i], options[i])
    wCursor = win32gui.GetCursorPos()
    win32gui.TrackPopupMenu(wSystraySubmenu, 0, wCursor[0], wCursor[1], 0, hWnd, None)
    win32gui.PostMessage(hWnd, win32con.WM_NULL, 0, 0)

def submenu_systray(hWnd):
    wOptions = []
    wSignals = []
    wOptions.append(submenu_exit)
    wSignals.append(WM_SUBMENU_EXIT)
    wOptions.append(submenu_prev)
    wSignals.append(WM_SUBMENU_PREV)
    wOptions.append(submenu_next)
    wSignals.append(WM_SUBMENU_NEXT)
    wOptions.append(submenu_show)
    wSignals.append(WM_SUBMENU_SHOW)
    wOptions.append(submenu_hide)
    wSignals.append(WM_SUBMENU_HIDE)
    wOptions.append(submenu_reset)
    wSignals.append(WM_SUBMENU_RESET)
    submenu(hWnd, wOptions, wSignals)

def systray(name = "Systray", method = wndProc):
    global hInstance, hSystray
    if hSystray:
        return
    icon = 0
    try:
        icon = win32gui.ExtractIcon(hInstance, systray_icon_path, systray_icon_id)
    except:
        #print("default_icon")
        pass
    try:
        wc = win32gui.WNDCLASS()
        wc.lpszClassName  = name
        wc.lpszMenuName   = ""
        wc.hInstance      = hInstance; #!!!
        wc.style          = win32con.CS_VREDRAW | win32con.CS_HREDRAW
        wc.hIcon          = 0
        wc.hCursor        = 0
        wc.hbrBackground  = 0
        wc.cbWndExtra     = 0
        wc.lpfnWndProc    = method
        atom = win32gui.RegisterClass(wc)
    except:
        #print("class_exists")
        pass
    
    hSystray = win32gui.CreateWindow(name, name, 0, 0, 0, 0, 0,
                                     None, None, hInstance, None)
    
    wSystray = win32gui.NIF_ICON | win32gui.NIF_MESSAGE | win32gui.NIF_TIP
    wSystrayParams = (hSystray, 0, wSystray, WM_SYSTRAY, icon, name)
    win32gui.Shell_NotifyIcon(win32gui.NIM_ADD, wSystrayParams)

def systray_remove():
    global hSystray
    #print("systray_remove")
    if hSystray:
        win32gui.Shell_NotifyIcon(win32gui.NIM_DELETE, (hSystray, 0))
        win32gui.CloseWindow(hSystray)
        hSystray = None
    #win32api.ExitProcess(0)

def window(name = "Window", method = wndProc):
    global hInstance, hWindow
    if hWindow:
        #win32gui.SetFocus(hWindow)
        win32gui.SetForegroundWindow(hWindow)
        win32gui.ShowWindow(hWindow, 1)
        return
    icon = 0
    try:
        icon = win32gui.ExtractIcon(hInstance, app_icon_path, app_icon_id)
        #icon = win32gui.LoadIcon(hInstance, win32con.MakeIntResource(107))
        #icon = win32gui.ExtractIcon(hInstance, "Backdrop.exe", 0) #107)
    except:
        #print("default_icon")
        pass
    try:
        wc = win32gui.WNDCLASS()
        wc.lpszClassName  = name
        wc.lpszMenuName   = ""
        wc.hInstance      = hInstance; #!!!
        wc.style          = win32con.CS_VREDRAW | win32con.CS_HREDRAW
        wc.hIcon          = icon # LoadIcon(hInstance, MakeIntResource(107))
        wc.hCursor        = 0 # MakeIntResource(32512)
        wc.hbrBackground  = 0 # CreateSolidBrush(0)
        wc.cbWndExtra     = 0 # IDC_APP_CLASS
        wc.lpfnWndProc    = method #win32gui.DefWindowProc
        atom = win32gui.RegisterClass(wc)
    except:
        #print("class_exists")
        pass
    
    #hWindow = win32gui.CreateWindowEx(win32con.WS_EX_LAYERED,
    #                                  wc.lpszClassName, name,
    #                                  win32con.WS_OVERLAPPEDWINDOW,
    #                                  win32con.CW_USEDEFAULT, 0,
    #                                  win32con.CW_USEDEFAULT, 0,
    #                                  None, None, hInstance, None)
    hWindow = win32gui.CreateWindow(wc.lpszClassName, name,
                                    win32con.WS_OVERLAPPEDWINDOW,
                                    win32con.CW_USEDEFAULT, 0,
                                    win32con.CW_USEDEFAULT, 0,
                                    None, None, hInstance, None)
    
    win32gui.SetWindowLong(hWindow, win32con.GWL_EXSTYLE, win32con.WS_EX_LAYERED)
    #win32gui.SetLayeredWindowAttributes(hWindow, 0, 0, win32con.LWA_COLORKEY)
    win32gui.SetLayeredWindowAttributes(hWindow, background, 0, win32con.LWA_COLORKEY)

    win32gui.ShowWindow(hWindow, win32con.SW_NORMAL)
    #win32gui.UpdateWindow(hWindow)

def window_refresh():
    global hWindow
    win32gui.InvalidateRect(hWindow, None, True)

def window_remove():
    global hWindow
    #print("window_remove", hWindow)
    if hWindow:
        #win32gui.CloseWindow(hWindow)
        win32gui.DestroyWindow(hWindow)
        hWindow = None

def process(hWnd = 0):
    msg = None
    if win32gui.PeekMessage(hWnd, 0, 0, win32con.PM_NOREMOVE)[0]:
        msg = win32gui.GetMessage(hWnd, 0, 0)
        msg = (msg[1],)
        win32gui.TranslateMessage(*msg)
        win32gui.DispatchMessage(*msg)
    #win32gui.InvalidateRect(hWnd, None, True) #!!!
    #win32gui.PumpWaitingMessages()

#print(sys.argv) # wWinMain: sys.__wargv from console context
if __name__ == "__main__":
    app()
