# Simple Calculator Program

# Ask the user for input
num1 = float(input("Enter first number: "))
operator = input("Enter operator (+, -, *, /, ^, mod, nth-root): ")
num2 = float(input("Enter second number: "))

# Perform calculation
if operator == "+":
    result = num1 + num2
elif operator == "-":
    result = num1 - num2
elif operator == "*":
    result = num1 * num2
elif operator == "/":
    if num2 != 0:
        result = num1 / num2
    else:
        result = "Error! Division by zero."
elif operator == "^" :
    result = num1 ** num2
elif operator == "mod":
    if num2 !=0 :
        result = num1 % num2
    else:
        result = "Oops, sorry that's undefined."
elif operator == "nth-root" :
    if num2 !=0 :
        result = num1 ** (1/num2)
    else:
        result = "Oops, sorry that's undefined."
else:
    result = "Invalid operator!"

# Display result
print("Result:", result)
