import subprocess
import tkinter as tk
from tkinter import messagebox
import os

from SystemUtils import SystemUtils
from ExcelUtils  import ExcelUtils

class FrontEnd:
    def __do_nothing(self): # 什么都不做
        pass

    def __edit_name_list(self):
        self.system_utils.edit_with_notepad(
            self.system_utils.get_name_list_path() # 编辑名单文件
        )
    
    def __edit_seat_set(self):
        self.system_utils.edit_with_notepad(
            self.system_utils.get_seat_set_path() # 编辑座位分布文件
        )
    
    def __create_new_arrangement(self) -> None: # 生成一个裸的座位表文件
        result = subprocess.run(
            [self.system_utils.get_program_path()], 
            capture_output=True, 
            text=True, 
            cwd=self.system_utils.get_src_path() # 指定工作路径
        )
        filename = result.stdout.strip()

        if filename == "":
            messagebox.showwarning("警告", "座位的数量必须与学生的总数一致!")
        else:
            xlsxname = self.excel_utils.make_xlsx_file(filename) # 生成 excel 文件
            self.system_utils.edit_xlsx_file(
                self.system_utils.get_xlsx_file_path(xlsxname)
            ) # 打开 excel 文件

    def __open_xlsx_folder(self): # 打开历史记录文件夹
        os.startfile(self.system_utils.get_xlsx_file_path(""))

    def __init__(self, system_utils: SystemUtils, excel_utils: ExcelUtils):
        self.__do_nothing() # 什么都没用
        self.padx = 5
        self.pady = 5
        self.system_utils = system_utils
        self.excel_utils  = excel_utils

        self.window = tk.Tk()
        self.window.resizable(False, False) # 禁止窗口大小调节
        self.window.title("随机排座 v0.1 beta")

        self.frame = tk.Frame(self.window, padx=10, pady=10)
        self.frame.pack()

        self.button1 = tk.Button(self.frame, text="修改班级名单", command=self.__edit_name_list, padx=self.padx, pady=self.pady)
        self.button1.grid(row=0, column=0)

        self.button2 = tk.Button(self.frame, text="修改座位分布", command=self.__edit_seat_set, padx=self.padx, pady=self.pady)
        self.button2.grid(row=0, column=1)

        self.button3 = tk.Button(self.frame, text="生成新座位表", command=self.__create_new_arrangement, padx=self.padx, pady=self.pady)
        self.button3.grid(row=0, column=2)

        self.button4 = tk.Button(self.frame, text="查看历史记录", command=self.__open_xlsx_folder, padx=self.padx, pady=self.pady)
        self.button4.grid(row=0, column=3)

    def run(self):
        self.window.mainloop()

if __name__ == "__main__":
    system_utils = SystemUtils()
    excel_utils  = ExcelUtils (system_utils)
    front_end    = FrontEnd   (system_utils, excel_utils)
    front_end.run()