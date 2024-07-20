import tkinter as tk
from tkinter import messagebox


class PasswordStrengthChecker(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Password Strength Checker")
        self.geometry("600x200")
        self.configure(bg='white')

        self.label = tk.Label(self, text="Enter a password between 8-32 characters:", bg='white')
        self.label.pack(pady=10)

        self.password_field = tk.Entry(self, show='*', width=50)
        self.password_field.pack(pady=10)

        self.check_button = tk.Button(self, text="Check Strength", command=self.check_password_strength)
        self.check_button.pack(pady=10)

        self.result_label = tk.Label(self, text="", bg='white')
        self.result_label.pack(pady=10)

    def check_password_strength(self):
        password = self.password_field.get()
        strength_score = self.calculate_password_strength(password)
        self.result_label.config(text=f"Password: {password} | Strength Score: {strength_score}/10")

    def calculate_password_strength(self, password):
        score = 0
        if 8 <= len(password) <= 32:
            score += 1
            if len(password) >= 12:
                score += 1
            if len(password) >= 16:
                score += 1
            if any(c.islower() for c in password):
                score += 1
            if any(c.isupper() for c in password):
                score += 1
            if any(c.isdigit() for c in password):
                score += 1
            if any(c in '!@#$%^&*()' for c in password):
                score += 1
            if (len(password) >= 12 and any(c.islower() for c in password) and 
                any(c.isupper() for c in password) and any(c.isdigit() for c in password) and 
                any(c in '!@#$%^&*()' for c in password)):
                score += 1
        return score

if __name__ == "__main__":
    app = PasswordStrengthChecker()
    app.mainloop()
