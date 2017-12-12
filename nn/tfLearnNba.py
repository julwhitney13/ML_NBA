from __future__ import print_function

import numpy as np
import tflearn
# Load CSV file, indicate that the first column represents labels
from tflearn.data_utils import load_csv

team_dict = {
    'Philadelphia 76ers': 1,
    'Minnesota Timberwolves': 2,
    'Denver Nuggets': 3,
    'Milwaukee Bucks': 4,
    'Brooklyn Nets': 5,
    'Charlotte Hornets': 6,
    'Oklahoma City Thunder': 7,
    'Cleveland Cavaliers': 8,
    'Washington Wizards': 9,
    'Miami Heat': 10,
    'New Orleans Pelicans': 11,
    'Los Angeles Lakers': 12,
    'Atlanta Hawks': 13,
    'Houston Rockets': 14,
    'Orlando Magic': 15,
    'Dallas Mavericks': 16,
    'Golden State Warriors': 17,
    'Toronto Raptors': 18,
    'Los Angeles Clippers': 19,
    'Boston Celtics': 20,
    'San Antonio Spurs': 21,
    'Detroit Pistons': 22,
    'Memphis Grizzlies': 23,
    'Utah Jazz': 24,
    'Indiana Pacers': 25,
    'New York Knicks': 26,
    'Phoenix Suns': 27,
    'Sacramento Kings': 28,
    'Chicago Bulls': 29,
    'Portland Trail Blazers': 30
}

def preprocess():
    team_stats, _ = load_csv("TeamStats_15-16.csv")
    opponent_stats, _ = load_csv("OpponentStats_15-16.csv")

    new_team = {}
    for l in team_stats:
        if team_dict.get(l[0]):
            l[0] = team_dict.get(l[0])
            new_team[l[0]] = l

    new_opponent = {}
    for l in opponent_stats:
        if team_dict.get(l[0]):
            l[0] = team_dict.get(l[0])
            new_opponent[l[0]] = l

    # print(new_team)
    # print(new_opponent)
    combined_stats = []
    for i in range(1, 31):
        combined_stats.append(new_team.get(i) + new_opponent.get(31-i))

    return combined_stats

def validate():
    results = []
    game_results, _ = load_csv("GameResults_15-16.csv")
    for l in game_results:
        l[1] = team_dict.get(l[1])
        l[3] = team_dict.get(l[1])


data, labels = load_csv('Game1415.csv', target_column=0, categorical_labels=True, n_classes=2)

# Build neural network
net = tflearn.input_data(shape=[None, len(data[0])])
fc1 = tflearn.fully_connected(net, 32)
fc2 = tflearn.fully_connected(fc1, 32)
fc3 = tflearn.fully_connected(fc2, 2, activation='softmax')
net = tflearn.regression(fc3)

# Define model
model = tflearn.DNN(net)

model.get_weights(fc3.W)
print(len(model.get_weights(fc3.W)))
# Start training (apply gradient descent algorithm)
model.fit(data, labels, n_epoch=10, batch_size=16, show_metric=True)

# Let's create some data for DiCaprio and Winslet
validate = preprocess()

# Predict surviving chances (class 1 results)
pred = model.predict(validate)
i = 0
for l in validate:
    print(l[0], "vs", l[13], pred[i][1])
    i = i + 1

# print("", pred[0][1])
# print("cavs v bulls:", pred[1][1])
# print("pel v warriors: ", pred[2][1])
# print(pred)
