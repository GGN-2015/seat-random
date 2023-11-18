import datetime
from openpyxl    import Workbook
from SystemUtils import SystemUtils

# 如何修改 excel 文件
class ExcelUtils:
    def __init__(self, system_utils: SystemUtils) -> None:
        self.system_utils       = system_utils
        self.empty_place_holder = "" # 空位占位符

    def get_time_now(self) -> str:
        now = datetime.datetime.now()
        formatted_date = now.strftime("%Y-%m-%d")
        formatted_time = now.strftime("%H-%M-%S")
        return formatted_date + "_" + formatted_time
    
    def load_table_from_raw(self, raw_filename) -> list: # 从 c++ 输出的原始文件加载座位表
        arr = []
        for line in open(self.system_utils.get_history_file_path(raw_filename), encoding="utf-8"):
            line = line.strip()

            if line != "":
                arr.append(line.split(","))
        col_cnt = max([len(subarr) for subarr in arr]) # 计算列数
        row_cnt = len(arr)                             # 计算行数
        for i in range(len(arr)):
            while len(arr[i]) < col_cnt:
                arr[i].append(self.empty_place_holder)
        return row_cnt, col_cnt, arr
    
    def dump_xlsx_file(self, row_cnt, col_cnt, arr, excel_file_name): # 把数据存储到 excel 文件中
        workbook = Workbook()
        worksheet = workbook.active
        worksheet.cell(row=1, column=1, value="Hello, World!")
        print(self.system_utils.get_xlsx_file_path(excel_file_name))
        workbook.save(self.system_utils.get_xlsx_file_path(excel_file_name))

    def make_xlsx_file(self, raw_filename) -> str: # 创建新的 excel 文件
        excel_file_name       = self.get_time_now() + ".xlsx"
        row_cnt, col_cnt, arr = self.load_table_from_raw(raw_filename)
        self.dump_xlsx_file(row_cnt, col_cnt, arr, excel_file_name)
        print(arr)
        return excel_file_name