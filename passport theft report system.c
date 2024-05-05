from datetime import datetime

class PassportTheftReportSystem:
    def __init__(self):
        self.reports = {}

    def ask_place(self):
        place = input("Where did it happen? (Place): ") 
        crowded = input("Was it a crowded area? (yes/no): ")
        return place, crowded.lower() == 'yes'

    def ask_time_date(self):
        year = int(input("Year of incident: "))
        month = int(input("Month of incident: "))
        day = int(input("Day of incident: "))
        return year, month, day

    def ask_passport_id(self):
        return input("Please provide your passport ID number: ")

    def ask_basic_info(self):
        while True:
            phone_number = input("Please provide your phone number: ")
            if len(phone_number) == 10 and phone_number.isdigit():
                break
            else:
                print("Please enter a 10-digit numeric phone number.")
        address = input("Please provide your address: ")
        return {'phone_number': phone_number, 'address': address}

    def print_statement(self, crowded, days_passed):
        if days_passed > 15:
            return "We can't find your passport. Please apply for a new one."
        elif crowded:
            if days_passed > 6:
                return "Your passport has been recovered. You can collect it now."
            else:
                return f"Your passport will be recovered in {6 - days_passed} days."
        else:
            return "we can't find u apply for new."
                      
    def report_theft(self):
        print("===== Passport Theft Report System =====")
        while True:
            name = input("Enter your name: ")
            if name not in self.reports:
                self.reports[name] = {}

            place, crowded = self.ask_place()
            year, month, day = self.ask_time_date()
            incident_date = datetime(year, month, day)
            current_date = datetime.now()
            days_passed = (current_date - incident_date).days
            print_statement = self.print_statement(crowded, days_passed)
            print(print_statement)

            if "apply for new" in print_statement:
                break

            passport_id = self.ask_passport_id()
            basic_info = self.ask_basic_info()

            # Store report information including 'time_date'
            self.reports[name] = {
                'place': place,
                'crowded': crowded,
                'time_date': incident_date.strftime("%Y-%m-%d"),  # Store incident date as string
                'passport_id': passport_id,
                'basic_info': basic_info,
                'report_date': current_date.strftime("%Y-%m-%d %H:%M:%S")  # Store report date with time
            }

            another_report = input("Do you want to report another theft? (yes/no): ")
            if another_report.lower() != 'yes':
                break

    def get_report_by_name(self, reported_name):
        if reported_name in self.reports:
            report_info = self.reports[reported_name]
            incident_date = datetime.strptime(report_info['time_date'], "%Y-%m-%d")
            days_passed = (datetime.now() - incident_date).days
            crowded = report_info.get('crowded', False)
            message = self.print_statement(crowded, days_passed)
            return report_info, message
        else:
            return "No report found for this name.", None

if __name__ == "__main__":
    report_system = PassportTheftReportSystem()
    report_system.report_theft()
    search_name = input("Enter the name to search for the report: ")
    report_info, message = report_system.get_report_by_name(search_name)
    if report_info:
        print("Reported Person's Details:")
        for key, value in report_info.items():
            print(f"{key}: {value}")
        print("\nPassport Recovery Status:")
        print(message)
    else:
        print(message)
