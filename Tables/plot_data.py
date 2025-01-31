# Import necessary libraries
import pandas as pd
import matplotlib.pyplot as plt

# Load your dataset (replace 'file_path' with the path to your CSV file)
file_path = 'C:/Users/Vedran/Desktop/AirQualityApp/Tables/air_quality_db_excel.csv'  # Replace with your file's path
data = pd.read_csv(file_path)

# Convert the 'timestamp' column to datetime format for accurate plotting
data['timestamp'] = pd.to_datetime(data['timestamp'])

# Plot AQI over time
plt.figure(figsize=(10, 6))
plt.plot(data['timestamp'], data['aqi'], label='AQI', color='blue', marker='o')
plt.title('AQI Over Time')
plt.xlabel('Date')
plt.ylabel('AQI')
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()

# Plot PM2.5 over time
plt.figure(figsize=(10, 6))
plt.plot(data['timestamp'], data['pm25'], label='PM2.5', color='green', marker='o')
plt.title('PM2.5 Over Time')
plt.xlabel('Date')
plt.ylabel('PM2.5 (µg/m³)')
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()

# Plot PM10 over time
plt.figure(figsize=(10, 6))
plt.plot(data['timestamp'], data['pm10'], label='PM10', color='red', marker='o')
plt.title('PM10 Over Time')
plt.xlabel('Date')
plt.ylabel('PM10 (µg/m³)')
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
