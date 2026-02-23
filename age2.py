from datetime import date

# Prompt user for input
year = int(input("Enter birth year (YYYY): "))
month = int(input("Enter birth month (1-12): "))
day = int(input("Enter birth day (1-31): "))

try:
    birth_date = date(year, month, day)
    today = date.today()

    # Calculate age
    age = today.year- birth_date.year

    # Adjust if birthday hasn't happened yet this year
    if (today.month, today.day) < (birth_date.month, birth_date.day):
        age -= 1

    print(f"You are {age} years old.")

except ValueError:
    print("Invalid date entered. Please check your inputs.")


