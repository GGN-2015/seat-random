import datetime

# 如何修改 excel 文件
class ExcelUtils:
    def __init__(self) -> None:
        pass

    def get_time_now(self) -> str:
        now = datetime.datetime.now()
        formatted_date = now.strftime("%Y-%m-%d")
        formatted_time = now.strftime("%H:%M:%S")
        return formatted_date + " " + formatted_time

    def make_xlsx_file(self, raw_filename) -> str: # 创建新的 excel 文件
        excel_file_name = self.get_time_now() + ".xlsx"
        return excel_file_name