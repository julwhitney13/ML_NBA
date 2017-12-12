from __future__ import print_function
import numpy as np
import tflearn
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

def preprocess(team_file, opponent_file):
    team_stats, _ = load_csv(team_file)
    opponent_stats, _ = load_csv(opponent_file)

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

    return new_team, new_opponent

def validation_stats(game_file="GameResults_15-16.csv", team_file="TeamStats_15-16.csv", opponent_file="OpponentStats_15-16.csv"):
    team_stats, opponent_stats = preprocess(team_file, opponent_file)

    results = []
    game_results, labels = load_csv(game_file, target_column=0, categorical_labels=True, n_classes=2)
    for l in game_results:
        team_num = team_dict.get(l[0])
        opponent_num  = team_dict.get(l[1])
        new_l = team_stats.get(team_num) + opponent_stats.get(opponent_num)
        results.append(new_l)
    return results, labels

year1516_data, year1516_labels = validation_stats()
year1617_data, year1617_labels = validation_stats("GameResults_16-17.csv", "TeamStats_16-17.csv", "OpponentStats_16-17.csv")
year1415_data, year1415_labels = load_csv('Game1415.csv', target_column=0, categorical_labels=True, n_classes=2)

data = np.concatenate((year1415_data, year1516_data))
labels = np.concatenate((year1415_labels, year1516_labels))
val_results = year1617_data
val_labels = year1617_labels

# Build neural network
net = tflearn.input_data(shape=[None, len(data[0])])
fc1 = tflearn.fully_connected(net, 32, trainable=True)
fc2 = tflearn.fully_connected(fc1, 32, trainable=True)
fc3 = tflearn.fully_connected(fc2, 2, activation='softmax')
net = tflearn.regression(fc3, optimizer='adam')

# Define model
model = tflearn.DNN(net, tensorboard_verbose=3)

# model.get_weights(fc2.W)
# model.set_weights(fc2.W, np.random.rand(32, 32))

model.fit(data, labels, n_epoch=30, batch_size=16, show_metric=True, validation_set=(val_results, val_labels), validation_batch_size=16)

# validate, _ = preprocess()

# pred = model.predict(validate)
# i = 0
# for l in validate:
#     print(l[0], "vs", l[13], pred[i][1])
#     i = i + 1
#
# print("", pred[0][1])
# print("cavs v bulls:", pred[1][1])
# print("pel v warriors: ", pred[2][1])
# print(pred)
