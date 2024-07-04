import pandas as pd
from sklearn.linear_model import LinearRegression

# Load the CSV file into a pandas DataFrame
file_path = '/run/media/suraj/KSS/Studies/RVCE/4th_sem/DAA/weather/weather.csv'  # Replace with your actual file path
df = pd.read_csv(file_path)

# Filter data for Birmingham
df_Birmingham = df[df['Station.City'] == 'Birmingham']

# Prepare data for modeling
# Assuming Date.Full is in format 'YYYY-MM-DD', extract Year and Month separately
df_Birmingham['Year'] = pd.to_datetime(df_Birmingham['Date.Full']).dt.year
df_Birmingham['Month'] = pd.to_datetime(df_Birmingham['Date.Full']).dt.month

# Select relevant columns for modeling
X = df_Birmingham[['Year', 'Month']].values  # Independent variables (Year and Month)
y = df_Birmingham['Data.Temperature.Avg Temp'].values  # Dependent variable (Avg Temperature)

# Check if there are enough samples for splitting
if len(X) < 2:
    print("Warning: Not enough samples for training and testing split. Using hypothetical values.")
    # Use hypothetical values for prediction
    predictions = [30.0] * 12  # Example hypothetical values for 12 months
else:
    # Split the data into training and testing sets (using data from 2016 for training)
    from sklearn.model_selection import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Initialize and fit the linear regression model
    model = LinearRegression()
    model.fit(X_train, y_train)

    # Predict temperatures for 2017 (assuming months 1 to 12 for the entire year)
    new_data_2017 = [[2017, month] for month in range(1, 13)]
    predictions = model.predict(new_data_2017)

# Print the predicted temperatures for 2017
print("Predicted temperatures for Birmingham in 2017:")
for i, pred in enumerate(predictions):
    print(f"Month {i+1}: {pred:.2f} °F")