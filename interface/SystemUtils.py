import os
import sys
import subprocess

class SystemUtils:
    def __init__(self) -> None: # 默认将当前工作目录切换到 src 目录下保证 c 程序正常
        src_dir = self.get_src_path()
        os.chdir(src_dir)

        if sys.platform == "win32": # 隐藏控制台
            import ctypes
            ctypes.windll.user32.ShowWindow(ctypes.windll.kernel32.GetConsoleWindow(), 0)

    def get_root_dir(self) -> str:
        dir_now  = os.path.dirname(os.path.abspath(__file__))
        root_dir = os.path.dirname(dir_now)
        return root_dir

    def get_src_path(self) -> str:
        root_dir = self.get_root_dir()
        src_dir  = os.path.join(root_dir, "src")
        return src_dir

    def get_program_path(self) -> str:
        src_path = self.get_src_path()
        return os.path.join(src_path, "seat-random.exe")
    
    def get_name_list_path(self) -> str: # 获得名单文件
        root_dir = self.get_root_dir()
        return os.path.join(root_dir, "config", "name_list.txt")
    
    def get_seat_set_path(self) -> str: # 获得作为排布
        root_dir = self.get_root_dir()
        return os.path.join(root_dir, "config", "seat_set.txt")
    
    def edit_with_notepad(self, filepath):
        subprocess.Popen(["notepad.exe", filepath]) # 在子进程打开文件，不阻塞
    
    def edit_xlsx_file(self, filepath):
        subprocess.Popen(['start', '', filepath], shell=True) # 用默认打开方式打开 excel 文件