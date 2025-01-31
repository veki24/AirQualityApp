# Import necessary libraries
import pandas as pd
import matplotlib.pyplot as plt

# Load your dataset (replace 'file_path' with the path to your CSV file)
file_path = 'air_quality_db_excel.csv'  # Replace with your file's path
data = pd.read_csv(file_path)

# Convert the 'timestamp' column to datetime format for accurate plotting
data['timestamp'] = pd.to_datetime(data['timestamp'])

# Create an Area Chart for AQI, PM2.5, and PM10
plt.figure(figsize=(12, 6))
plt.stackplot(
    data['timestamp'],  # X-axis data
    data['aqi'],        # Y1 data
    data['pm25'],       # Y2 data
    data['pm10'],       # Y3 data
    labels=['AQI', 'PM2.5', 'PM10'],  # Legend labels
    colors=['blue', 'green', 'red'],  # Fill colors for each area
    alpha=0.7           # Transparency level
)
plt.title('Cumulative AQI, PM2.5, and PM10 Over Time')  # Chart title
plt.xlabel('Date')  # X-axis label
plt.ylabel('Value')  # Y-axis label
plt.legend(loc='upper left')  # Legend position
plt.grid(True)  # Add grid lines
plt.xticks(rotation=45)  # Rotate x-axis labels
plt.tight_layout()  # Adjust layout for better readability
plt.show()
