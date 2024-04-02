import random
def getplayer(filename):
    playerbase = []
    with open (filename) as file:
        next(file)
        for line in file:
            player = []
            playername, skilllevel = line.strip().split()
            skilllevel = int(skilllevel)
            player.append(skilllevel)
            player.append(playername)
            playerbase.append(player)
            print(playername, " was added.")
    playerbase.sort(key=lambda x: (x[0], random.random()))
    return playerbase

def createteams(playerbase, balanced):
    maxteamsize = 5
    team1 = []
    team2 = []
    if balanced == 'n' or balanced == 'N':
        team1.append(playerbase.pop(len(playerbase)-1))
        team2.append(playerbase.pop(len(playerbase)-1))
        team2.append(playerbase.pop(len(playerbase)-1))
        team1.append(playerbase.pop(len(playerbase)-1))
        team1.append(playerbase.pop(len(playerbase)-1))
        team2.append(playerbase.pop(len(playerbase)-1))
        team1.append(playerbase.pop(len(playerbase)-1))
        team2.append(playerbase.pop(len(playerbase)-1))
        team1.append(playerbase.pop(len(playerbase)-1))
        team2.append(playerbase.pop(len(playerbase)-1))
    if balanced == 'y' or balanced == 'Y':
        while len(playerbase) > 0:
            team1.append(playerbase.pop(len(playerbase)-1))
            team2.append(playerbase.pop(len(playerbase)-1))
            
    totalteam1 = team_total(team1)
    totalteam2 = team_total(team2)
    if totalteam1 - totalteam2 == 2:
        attempt = 1
        while attempt == 1:
            t1 = random.randint(1, 4)
            t2 = random.randint(1, 4)
            player1 = team1[t1]
            player2 = team2[t2]
            team1.remove(player1)
            team2.remove(player2)
            team2.append(player1)
            team1.append(player2)
            totalteam1 = team_total(team1)
            totalteam2 = team_total(team2)
    print('\nTeam 1:\tRating: ', totalteam1)
    for player in team1:
        print(player[1], player[0])
    print('Team 2:\tRating: ', totalteam2)
    for player in team2:
        print(player[1], player[0])
    choice = input("Would you like to switch a single player or reroll? (y/n/r)")
    changesingle(team1, team2, choice)
    
def changesingle(team1, team2, choice):
    if choice.lower() == 'y':
        while True:
            player1_name = input("Enter the name of the player to swap from team 1: ")
            player1 = None
            for p in team1:
                if p[1] == player1_name:
                    player1 = p
                    break
            if player1 is None:
                print("Player not found in team 1.")
                continue
            player2_name = input("Enter the name of the player to swap with from team 2: ")
            player2 = None
            for p in team2:
                if p[1] == player2_name:
                    player2 = p
                    break
            if player2 is None:
                print("Player not found in team 2.")
                continue
            team1.remove(player1)
            team2.remove(player2)
            team1.append(player2)
            team2.append(player1)
            print("Players swapped successfully!\nUPDATED TEAMS:\n")
            totalteam1 = team_total(team1)
            totalteam2 = team_total(team2)
            print('\nTeam 1:\tRating: ', totalteam1)
            for player in team1:
                print(player[1], player[0])
            print('Team 2:\tRating: ', totalteam2)
            for player in team2:
                print(player[1], player[0])
            break

def team_total(team):
    total = 0
    for player in team:
        total += player[0]
    return total

def main():
    filename = "players.txt"
    choice = 'yes'
    balanced = (input("Is the skill level tight? (y/n)"))
    while choice != 'n':
        playerbase = getplayer(filename)
        createteams(playerbase, balanced)
        choice = input("Reroll? (y/n)")
    print("Thank you for using the Ben code!")

main()
        
    
  
    
    
        