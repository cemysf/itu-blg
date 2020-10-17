import datetime
import json
import os
import psycopg2 as dbapi2
import re



from flask import Flask, session, redirect, url_for, escape, request
from flask import render_template
from flask.helpers import url_for
import psycopg2

class City:
        def __init__(self, ID, Name):
            self.ID = ID
            self.Name = Name
            self.Comments = [];

class Team:
    def __init__(self,ID,Name):
        self.ID = ID
        self.Name = Name
        self.Comments = []

class Player:
    def __init__(self,ID,Name):
        self.ID = ID
        self.Name = Name
        self.Comments = []

class Tournament:
    def __init__(self,ID,Name):
        self.ID = ID
        self.Name = Name
        self.Comments = []

class Comment:
    def __init__(self,ID,Text):
        self.ID = ID
        self.Text = Text

class Country:
        def __init__(self, ID, Name):
            self.ID = ID
            self.Name = Name

class Place:
    def __init__(self,ID,Name):
        self.ID = ID
        self.Name = Name

class Author:
    def __init__(self,ID,Name,WorkDescription):
        self.ID = ID
        self.Name = Name
        self.WorkDescription = WorkDescription

class Accommodation:
        def __init__(self, ID, Name):
            self.ID = ID
            self.Name = Name
            self.Comments= []

app = Flask(__name__)
app.secret_key = 'this key is supposed to be secret'

def connect_db():
    conn = psycopg2.connect(app.config['dsn'])
    cursor = conn.cursor()
    return conn, cursor

def get_elephantsql_dsn(vcap_services):
    """Returns the data source name for ElephantSQL."""
    parsed = json.loads(vcap_services)
    uri = parsed["elephantsql"][0]["credentials"]["uri"]
    match = re.match('postgres://(.*?):(.*?)@(.*?)(:(\d+))?/(.*)', uri)
    user, password, host, _, port, dbname = match.groups()
    dsn = """user='{}' password='{}' host='{}' port={}
             dbname='{}'""".format(user, password, host, port, dbname)
    return dsn


@app.route('/')
def home_page():
    if not (session.get('isValid') == True or session.get('isValid') == False):
        session['isValid'] = False
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT City.City_ID, City.City_Name, Country.Country_Name as City_CountryName FROM City INNER JOIN Country ON (City.City_CountryID = Country.Country_ID) ORDER BY City.City_Name ASC """
        cursor.execute(statement)
        tempList = cursor.fetchmany(5)
        cities=[]
        i = 1
        for City_ID,City_Name,City_CountryName in tempList:
           city=(City(City_ID,City_Name))
           country = City_CountryName
           cities.append([i,(city),country])
           i = i + 1
        players = []
        statement = """SELECT Player.Player_ID, Player.Player_Name, Team.Team_Name as Player_TeamName FROM Player INNER JOIN Team ON (Player.Player_TeamID = Team.Team_ID) ORDER BY Player.Player_Name ASC """
        cursor.execute(statement)
        i = 1
        tempList = cursor.fetchmany(5)
        for Player_ID, Player_Name, Player_TeamName in tempList:
            player = Player(Player_ID,Player_Name)
            players.append([i,(player),Player_TeamName])
            i = i + 1
        teams=[]
        statement = """SELECT Team.Team_ID, Team.Team_Name, Team.Team_Total_Points, Country.Country_Name as Team_CountryName FROM Team INNER JOIN Country ON (Team.Team_CountryID = Country.Country_ID) ORDER BY Team.Team_Name ASC """
        cursor.execute(statement)
        i = 1
        tempList = cursor.fetchmany(5)
        for Team_ID, Team_Name, Team_Total_Points, Team_CountryName in tempList:
            team = Team(Team_ID,Team_Name)
            teams.append([i,(team),Team_Total_Points,Team_CountryName])
            i = i + 1
        tournaments=[]
        statement = """SELECT Tournament.Tournament_ID, Tournament.Tournament_Name, City.City_Name as City_Name FROM Tournament INNER JOIN City ON (Tournament.Tournament_CityID = City.City_ID) ORDER BY Tournament.Tournament_ID ASC """
        cursor.execute(statement)
        i = 1
        tempList = cursor.fetchmany(5)
        for Tournament_ID, Tournament_Name, City_Name in tempList:
            tournament = Tournament(Tournament_ID,Tournament_Name)
            tournaments.append([i,(tournament),City_Name])
            i = i + 1
        isAdmin = session['isValid']
    return render_template('home.html', CityList = cities, PlayerList = players, TeamList = teams, Tournament = tournaments, IsAdmin = isAdmin)


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            userName = request.form['username']
            userPassword = request.form['password']

            query = """ SELECT COUNT(*) FROM Admin WHERE Admin_Username = '{0}' AND Admin_Password= '{1}' """
            cursor.execute(query.format(userName,userPassword))

            a = cursor.fetchone()[0]

            if a >= 1:
                session['isValid'] = True
                return redirect(url_for('home_page'))
            return 'epic fail!!'

    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        query = """INSERT INTO Admin (Admin_Username, Admin_Password) VALUES ('ismail', 'deneme12')"""
        cursor.execute(query)
        return render_template('login.html')

@app.route('/logout')
def logout():
    session['isValid'] = False
    return redirect(url_for('home_page'))

@app.route('/riderlist')
def riderlist():
    now = datetime.datetime.now()
    return render_template('riderlist.html', current_time=now.ctime())

@app.route('/home')
def home2():
    now = datetime.datetime.now()
    return render_template('home.html', current_time=now.ctime())


#----------------------------------------------section city------------------------------

@app.route('/citylist')
def citylist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT City_ID, City_Name FROM City ORDER BY City_ID"""
        cursor.execute(statement)
        cities=[]
        for City_ID,City_Name in cursor:
           city=(City(City_ID,City_Name))
           cities.append(city)
           print(City_ID)
        for city in cities:
            statement = """SELECT City_Comment_Text FROM City_Comments WHERE City_ID = {0}"""
            cursor.execute(statement.format(city.ID))
            for City_Comment_Text in cursor:
                city.Comments.append(City_Comment_Text)
        isAdmin = session['isValid']
    return render_template('citylist.html', citylist = cities, IsAdmin = isAdmin)

@app.route('/citydelete/<id>')
def citydelete(id):
    if session['isValid'] == False:
        return "You are not authorized"
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        statement = """DELETE FROM City WHERE City_ID={0}"""
        cursor.execute(statement.format(id))
        connection.commit()
    return redirect(url_for('citylist'))

@app.route('/addcity', methods=['POST', 'GET'])
def addcity():
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Name = request.form['Name']
            CountryID = request.form['selectedValue']


            query = """CREATE TABLE IF NOT EXISTS City ( City_ID SERIAL PRIMARY KEY NOT NULL, City_Name CHAR(50) NOT NULL, City_CountryID INT REFERENCES Country (Country_ID) ON DELETE CASCADE ON UPDATE CASCADE    );"""
            cursor.execute(query)
            try:
                queryWithFormat = """INSERT INTO City (City_Name, City_CountryID) VALUES (%s, %s)"""
                cursor.execute(queryWithFormat, (Name, CountryID))
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('citylist'))
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Country_ID, Country_Name FROM Country ORDER BY Country_ID"""
        cursor.execute(statement)
        countries=[]
        for Country_ID,Country_Name in cursor:
           country=(Country(Country_ID,Country_Name))
           countries.append(country)
    return render_template('addcity.html', Countries = countries)

@app.route('/addcitycomment/<id>', methods=['POST', 'GET'])
def addcitycomment(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Comment = request.form['Comment']

            query = """CREATE TABLE IF NOT EXISTS City_Comments (
                                City_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                City_ID INTEGER REFERENCES City(City_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                City_Comment_Text CHAR(500) NOT NULL
                    );"""
            cursor.execute(query)


            try:
                queryWithFormat = """INSERT INTO City_Comments (City_ID, City_Comment_Text) VALUES (%s,%s)"""
                cursor.execute(queryWithFormat, (id, Comment))
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('citylist'))
    return render_template('addcitycomment.html', ID=id)

@app.route('/updatecity/<id>', methods=['POST', 'GET'])
def updatecity(id):
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            New_Name = request.form['Name']
            try:
                query = """UPDATE City SET City_Name='%s' WHERE City_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('citylist'))
    return render_template('updatecity.html', ID=id)

@app.route('/searchcity', methods=['POST', 'GET'])
def searchcity():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            textstr = request.form['textstr']
            cities = []
            try:
                query = """SELECT City_ID, City_Name FROM City WHERE City_Name like '%{0}%'"""
                cursor.execute(query.format(textstr))
                for City_ID, City_Name in cursor:
                    city = City(City_ID,City_Name)
                    cities.append(city)
                return render_template('citylist.html', citylist = cities)
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return "eeeee"
    return render_template('searchcity.html')

    """<script>
    function deleter(id) {
        window.location.href("/citydelete/id=" + id);
    }
    </script>"""

#----------------------------------------------section player------------------------------
@app.route('/playerlist')
def playerlist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        players = []
        statement = """SELECT Player_ID, Player_Name FROM Player ORDER BY Player_ID"""
        cursor.execute(statement)
        for Player_ID, Player_Name in cursor:
            player = Player(Player_ID,Player_Name)
            players.append(player)
        for player in players:
            statement = """SELECT Player_Comment_Text FROM Player_Comments WHERE Player_ID = {0}"""
            cursor.execute(statement.format(player.ID))
            for Player_Comment_Text in cursor:
                player.Comments.append(Player_Comment_Text)
        isAdmin = session['isValid']
    return render_template('playerlist.html', Players = players, IsAdmin = isAdmin)

@app.route('/searchplayer', methods=['POST', 'GET'])
def searchplayer():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            textstr = request.form['textstr']
            players = []
            try:
                query = """SELECT Player_ID, Player_Name FROM Player WHERE Player_Name like '%{0}%'"""
                cursor.execute(query.format(textstr))
                for Player_ID, Player_Name in cursor:
                    player = Player(Player_ID,Player_Name)
                    players.append(player)
                return render_template('playerlist.html', Players = players)
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return "eeeee"
    return render_template('searchplayer.html')

@app.route('/playerdelete/<id>')
def playerdelete(id):
    if session['isValid'] == False:
        return "You are not authorized"
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        statement = """DELETE FROM Player WHERE Player_ID={0}"""
        cursor.execute(statement.format(id))
        connection.commit()
    return redirect(url_for('playerlist'))

@app.route('/addplayer', methods=['POST', 'GET'])
def addplayer():
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Name = request.form['Name']
            TeamID = request.form['selectedValue']

            query = """CREATE TABLE IF NOT EXISTS Player ( Player_ID SERIAL PRIMARY KEY NOT NULL, Player_Name CHAR(50) NOT NULL, Player_TeamID INT REFERENCES Team (Team_ID) );"""
            cursor.execute(query)
            try:
                queryWithFormat = """INSERT INTO Player (Player_Name, Player_TeamID) VALUES (%s, %s)"""
                cursor.execute(queryWithFormat, (Name, TeamID))
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('playerlist'))
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Team_ID, Team_Name FROM Team ORDER BY Team_ID"""
        cursor.execute(statement)
        teams=[]
        for Team_ID,Team_Name in cursor:
           team=(Team(Team_ID,Team_Name))
           teams.append(team)
    return render_template('addplayer.html', Teams = teams)

@app.route('/addplayercomment/<id>', methods=['POST', 'GET'])
def addplayercomment(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Comment = request.form['Comment']

            query = """CREATE TABLE IF NOT EXISTS Player_Comments (
                                Player_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Player_ID INTEGER REFERENCES Player(Player_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                PLayer_Comment_Text CHAR(500) NOT NULL
                    );"""
            cursor.execute(query)


            try:
                queryWithFormat = """INSERT INTO Player_Comments (Player_ID, PLayer_Comment_Text) VALUES (%s,%s)"""
                cursor.execute(queryWithFormat, (id, Comment))
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('playerlist'))
    return render_template('addplayercomment.html', ID=id)

@app.route('/updateplayer/<id>', methods=['POST', 'GET'])
def updateplayer(id):
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            New_Name = request.form['Name']
            try:
                query = """UPDATE Player SET Player_Name='%s' WHERE Player_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('playerlist'))
    return render_template('updateplayer.html', ID=id)

#----------------------------------------------section tournament------------------------------

@app.route('/tournamentlist')
def tournamentlist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Tournament_ID, Tournament_Name FROM Tournament ORDER BY Tournament_ID"""
        cursor.execute(statement)
        tournaments = []
        for Tournament_ID, Tournament_Name in cursor:
            tournament = (Tournament(Tournament_ID, Tournament_Name))
            tournaments.append(tournament)
        for tournament in tournaments:
            statement = """SELECT Tournament_Comment_Text FROM Tournament_Comments WHERE Tournament_ID = {0}"""
            cursor.execute(statement.format(tournament.ID))
            for Tournament_Comment_Text in cursor:
                tournament.Comments.append(Tournament_Comment_Text)
        isAdmin = session['isValid']
    return render_template('tournamentlist.html', tournamentlist=tournaments, IsAdmin = isAdmin)

@app.route('/tournamentdelete/<id>')
def tournamentdelete(id):
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        statement = """DELETE FROM Tournament WHERE Tournament_ID={0}"""
        cursor.execute(statement.format(id))
        connection.commit()
    return redirect(url_for('tournamentlist'))

@app.route('/addtournament', methods=['POST', 'GET'])
def addtournament():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Name = request.form['Name']
            City_ID = request.form['selectedValue']

            query = """CREATE TABLE IF NOT EXISTS Tournament ( Tournament_ID SERIAL PRIMARY KEY NOT NULL, Tournament_Name CHAR(50) NOT NULL, Tournament_CityID INT REFERENCES City (City_ID) ON DELETE CASCADE ON UPDATE CASCADE);"""
            cursor.execute(query)
            try:
                queryWithFormat = """INSERT INTO Tournament (Tournament_Name, Tournament_CityID ) VALUES (%s, %s)"""
                cursor.execute(queryWithFormat, (Name, City_ID))
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('tournamentlist'))
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        statement = """SELECT City_ID, City_Name FROM City ORDER BY City_ID"""
        cursor.execute(statement)
        cities=[]
        for City_ID,City_Name in cursor:
            city=(City(City_ID,City_Name))
            cities.append(city)
    return render_template('addtournament.html', Cities = cities)

@app.route('/updatetournament/<id>', methods=['POST', 'GET'])
def updatetournament(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            New_Name = request.form['Name']
            try:
                query = """UPDATE Tournament SET Tournament_Name='%s' WHERE Tournament_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('tournamentlist'))
    return render_template('updatetournament.html', ID=id)



@app.route('/addtournamentcomment/<id>', methods=['POST', 'GET'])
def addtournamentcomment(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Comment = request.form['Comment']

            query = """CREATE TABLE IF NOT EXISTS Tournament_Comments (
                                Tournament_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Tournament_ID INTEGER REFERENCES Tournament(Tournament_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Tournament_Comment_Text CHAR(500) NOT NULL
                    );"""
            cursor.execute(query)

            try:
                queryWithFormat = """INSERT INTO Tournament_Comments (Tournament_ID, Tournament_Comment_Text) VALUES (%s,%s)"""
                cursor.execute(queryWithFormat, (id, Comment))
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('tournamentlist'))
    return render_template('addtournamentcomment.html', ID=id)

@app.route('/searchtournament', methods=['POST', 'GET'])
def searchtournament():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            textstr = request.form['textstr']
            tournaments = []
            try:
                query = """SELECT Tournament_ID, Tournament_Name FROM Tournament WHERE Tournament_Name like '%{0}%'"""
                cursor.execute(query.format(textstr))
                for Tournament_ID, Tournament_Name in cursor:
                    tournament = Tournament(Tournament_ID,Tournament_Name)
                    tournaments.append(tournament)
                return render_template('tournamentlist.html', tournamentlist = tournaments)
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return "eeeee"
    return render_template('searchtournament.html')


#----------------------------------------------section team------------------------------
@app.route('/teamlist')
def teamlist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Team_ID, Team_Name FROM Team ORDER BY Team_ID"""
        cursor.execute(statement)
        teams=[]
        for Team_ID,Team_Name in cursor:
           team=(Team(Team_ID,Team_Name))
           teams.append(team)
        for team in teams:
           statement = """SELECT Team_Comment_Text FROM Team_Comments WHERE Team_ID = {0}"""
           cursor.execute(statement.format(team.ID))
           for Team_Comment_Text in cursor:
               team.Comments.append(Team_Comment_Text)
        isAdmin = session['isValid']
    return render_template('teamlist.html', Teams=teams, IsAdmin = isAdmin)


@app.route('/addteam', methods=['POST', 'GET'])
def addteam():
    if request.method == 'POST':
        if session['isValid'] == False:
            return "You are not authorized"
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Name = request.form['Name']
            CountryID = request.form['selectedValue']

            query = """CREATE TABLE IF NOT EXISTS Team (
                                Team_ID SERIAL PRIMARY KEY NOT NULL,
                                Team_Name CHAR(50) NOT NULL,
                                Team_CountryID INT REFERENCES Country (Country_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Team_Total_Points INT DEFAULT 0
                    );"""
            cursor.execute(query)
            try:
                queryWithFormat = """INSERT INTO Team (Team_Name, Team_CountryID) VALUES (%s, %s)"""
                cursor.execute(queryWithFormat, (Name, CountryID))
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('teamlist'))
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Country_ID, Country_Name FROM Country ORDER BY Country_ID"""
        cursor.execute(statement)
        countries=[]
        for Country_ID,Country_Name in cursor:
           country=(Country(Country_ID, Country_Name))
           countries.append(country)
    return render_template('addteam.html', Countries = countries)

@app.route('/teamdelete/<id>')
def teamdelete(id):
    if session['isValid'] == False:
        return "You are not authorized"
    with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            statement = """DELETE FROM Team WHERE Team_ID={0}"""
            cursor.execute(statement.format(id))
            connection.commit()
    return redirect(url_for('teamlist'))

@app.route('/updateteam/<id>', methods=['POST', 'GET'])
def updateteam(id):
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            New_Name = request.form['Name']

            try:
                query = """UPDATE Team SET Team_Name='%s' WHERE Team_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('teamlist'))
    return render_template('updateteam.html', ID=id)

@app.route('/addteamcomment/<id>', methods=['POST', 'GET'])
def addteamcomment(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Comment = request.form['Comment']
            query = """CREATE TABLE IF NOT EXISTS Team_Comments (
                                Team_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Team_ID INTEGER REFERENCES Team(Team_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Team_Comment_Text CHAR(500) NOT NULL
                    );"""
            cursor.execute(query)
            try:
                query = """INSERT INTO Team_Comments (Team_ID, Team_Comment_Text)
                    VALUES (%s, %s)"""
                cursor.execute(query, (id, Comment))
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('teamlist'))
    return render_template('addteamcomment.html', ID=id)

@app.route('/searchteam', methods=['POST', 'GET'])
def searchteam():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            textstr = request.form['textstr']
            teams = []
            try:
                query = """SELECT Team_ID, Team_Name FROM Team WHERE Team_Name like '%{0}%'"""
                cursor.execute(query.format(textstr))
                for Team_ID, Team_Name in cursor:
                    team = Team(Team_ID,Team_Name)
                    teams.append(team)
                return render_template('teamlist.html', team_list = teams)
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return "eeeee"
    return render_template('searchteam.html')



#----------------------------------------------section country------------------------------

@app.route('/countrylist')
def countrylist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Country_ID, Country_Name FROM Country ORDER BY Country_ID"""
        cursor.execute(statement)
        countries=[]
        for Country_ID,Country_Name in cursor:
           country=(Country(Country_ID,Country_Name))
           countries.append(country)
        isAdmin = session['isValid']
    return render_template('countrylist.html', countrylist = countries, IsAdmin = isAdmin)
    
@app.route('/countrydelete/<id>')
def countrydelete(id):
    if session['isValid'] == False:
        return "You are not authorized"
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        statement = """DELETE FROM Country WHERE Country_ID={0}"""
        cursor.execute(statement.format(id))
        connection.commit()
    return redirect(url_for('countrylist'))

@app.route('/addcountry', methods=['POST', 'GET'])
def addcountry():
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Name = request.form['Name']

            query = """CREATE TABLE IF NOT EXISTS Country ( Country_ID SERIAL PRIMARY KEY NOT NULL, Country_Name CHAR(50) NOT NULL    );"""
            cursor.execute(query)

            queryWithFormat = """INSERT INTO Country (Country_Name) VALUES ( '{0}' )"""
            cursor.execute(queryWithFormat.format(Name))

        return redirect(url_for('countrylist'))
    return render_template('addcountry.html')

@app.route('/updatecountry/<id>', methods=['POST', 'GET'])
def updatecountry(id):
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            New_Name = request.form['Name']
            try:
                query = """UPDATE Country SET Country_Name='%s' WHERE Country_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('countrylist'))
    return render_template('updatecountry.html', ID=id)

@app.route('/searchcountry', methods=['POST', 'GET'])
def searchcountry():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            textstr = request.form['textstr']
            countries = []
            try:
                query = """SELECT Country_ID, Country_Name FROM Country WHERE Country_Name like '%{0}%'"""
                cursor.execute(query.format(textstr))
                for Country_ID, Country_Name in cursor:
                    country = Country(Country_ID,Country_Name)
                    countries.append(country)
                return render_template('countrylist.html', countrylist = countries)
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return "eeeee"
    return render_template('searchcountry.html')

#---------------------place-------------------
@app.route('/updateplace/<id>', methods=['POST', 'GET'])
def updateplace(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            New_Name = request.form['Name']
            try:
                query = """UPDATE Place SET Place_Name='%s' WHERE Place_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('placelist'))
    return render_template('updateplace.html', ID=id)

@app.route('/placecomments/<id>')
def placecomments(id):
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Place_Comment_ID, Place_Comment_Text
                        FROM Place_Comments WHERE Place_ID=%s
                        ORDER BY Place_Comment_ID""" % (id)
        cursor.execute(statement)
        comments=[]
        for Place_Comment_ID,Place_Comment_Text in cursor:
           comment=(Place(Place_Comment_ID,Place_Comment_Text))
           comments.append(comment)
    return render_template('placecomments.html', ID=id ,commentlist=comments)
    #----------------------------------------------------------

@app.route('/accommodationlist')
def accommodationlist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Accommodation_ID, Accommodation_Name FROM Accommodation ORDER BY Accommodation_ID"""
        cursor.execute(statement)
        accommodationies=[]
        for Accommodation_ID,Accommodation_Name in cursor:
           accommodation=(Accommodation(Accommodation_ID,Accommodation_Name))
           accommodationies.append(accommodation)
           print(Accommodation_ID)
        for accommodation in accommodationies:
            statement = """SELECT Accommodation_Comment_Text FROM Accommodation_Comments WHERE Accommodation_ID = {0}"""
            cursor.execute(statement.format(accommodation.ID))
            for Accommodation_Comment_Text in cursor:
                accommodation.Comments.append(Accommodation_Comment_Text)
    isAdmin = session['isValid']
    return render_template('accommodationlist.html', accommodationlist = accommodationies, IsAdmin = isAdmin)

@app.route('/accommodationdelete/<id>')
def accommodationdelete(id):
    if session['isValid'] == False:
        return "You are not authorized"
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        statement = """DELETE FROM Accommodation WHERE Accommodation_ID={0}"""
        cursor.execute(statement.format(id))
        connection.commit()
    return redirect(url_for('accommodationlist'))

@app.route('/addaccommodation', methods=['POST', 'GET'])
def addaccommodation():
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Name = request.form['Name']
            AccommodationID = request.form['selectedValue']


            query = """CREATE TABLE IF NOT EXISTS Accommodation ( Accommodation_ID SERIAL PRIMARY KEY NOT NULL, Accommodation_Name CHAR(50) NOT NULL, Accommodation_CityID INT REFERENCES City (City_ID) ON DELETE CASCADE ON UPDATE CASCADE    );"""
            cursor.execute(query)
            try:
                queryWithFormat = """INSERT INTO Accommodation (Accommodation_Name, Accommodation_CityID) VALUES (%s, %s)"""
                cursor.execute(queryWithFormat, (Name, AccommodationID))
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('accommodationlist'))
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT City_ID, City_Name FROM City ORDER BY City_ID"""
        cursor.execute(statement)
        cities=[]
        for City_ID,City_Name in cursor:
           city=(City(City_ID,City_Name))
           cities.append(city)
    return render_template('addaccommodation.html', Cities = cities)

@app.route('/addaccommodationcomment/<id>', methods=['POST', 'GET'])
def addaccommodationcomment(id):
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()

            Comment = request.form['Comment']

            query = """CREATE TABLE IF NOT EXISTS Accommodation_Comments (
                                Accommodation_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Accommodation_ID INTEGER REFERENCES Accommodation(Accommodation_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Accommodation_Comment_Text CHAR(500) NOT NULL
                    );"""
            cursor.execute(query)


            try:
                queryWithFormat = """INSERT INTO Accommodation_Comments (Accommodation_ID, Accommodation_Comment_Text) VALUES (%s,%s)"""
                cursor.execute(queryWithFormat, (id, Comment))
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('accommodationlist'))
    return render_template('addaccommodationcomment.html', ID=id)

@app.route('/updateaccommodation/<id>', methods=['POST', 'GET'])
def updateaccommodation(id):
    if session['isValid'] == False:
        return "You are not authorized"
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            New_Name = request.form['Name']
            try:
                query = """UPDATE Accommodation SET Accommodation_Name='%s' WHERE Accommodation_ID='%s' """ % (New_Name, id)
                cursor.execute(query)
                connection.commit()
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return redirect(url_for('accommodationlist'))
    return render_template('updateaccommodation.html', ID=id)

@app.route('/searchaccommodation', methods=['POST', 'GET'])
def searchaccommodation():
    if request.method == 'POST':
        with dbapi2.connect(app.config['dsn']) as connection:
            cursor = connection.cursor()
            textstr = request.form['textstr']
            accommodationies = []
            try:
                query = """SELECT Accommodation_ID, Accommodation_Name FROM Accommodation WHERE Accommodation_Name like '%{0}%'"""
                cursor.execute(query.format(textstr))
                for Accommodation_ID, Accommodation_Name in cursor:
                    accommodation = Accommodation(Accommodation_ID,Accommodation_Name)
                    accommodationies.append(accommodation)
                return render_template('accommodationlist.html', accommodationlist = accommodationies)
            except dbapi2.DatabaseError:
                connection.rollback()
                return "error happened"
        return "eeeee"
    return render_template('searchaccommodation.html')

#--------------------- Author -------------------------------------------

@app.route('/contactus')
def authorlist():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        retval = ""
        statement = """SELECT Author_Student_ID, Author_Name, Author_Work_Description FROM Author ORDER BY Author_Student_ID ASC"""
        cursor.execute(statement)
        authors=[]
        for Author_Student_ID, Author_Name, Author_Work_Description in cursor:
           author=(Author(Author_Student_ID,Author_Name,Author_Work_Description))
           authors.append(author)
    return render_template('contactus.html', authorlist=authors)

 #-------------------------------------------------------------------------









@app.route('/resetdb')
def reset_database():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()

        query = """DROP TABLE IF EXISTS COUNTER CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Accommodation CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS City CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Country CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Player CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Player_Comments CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Tournament_Comments CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Tournament CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Team_Comments CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Team CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Admin CASCADE"""
        cursor.execute(query)

        query = """DROP TABLE IF EXISTS Author CASCADE"""
        cursor.execute(query)

        connection.commit()
        return redirect(url_for('initialize_database'))



@app.route('/initdb')
def initialize_database():
    session['isValid'] = False
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()

        query = """CREATE TABLE IF NOT EXISTS Country (
                                Country_ID SERIAL PRIMARY KEY NOT NULL,
                                Country_Name CHAR(50) NOT NULL
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS City (
                                City_ID SERIAL PRIMARY KEY NOT NULL,
                                City_Name CHAR(50) NOT NULL,
                                City_CountryID INT REFERENCES Country (Country_ID) ON DELETE CASCADE ON UPDATE CASCADE
                    );"""
        cursor.execute(query)


        query = """CREATE TABLE IF NOT EXISTS Accommodation (
                                Accommodation_ID SERIAL PRIMARY KEY NOT NULL,
                                Accommodation_Name CHAR(50) NOT NULL,
                                Accommodation_CityID INT REFERENCES City (City_ID) ON DELETE CASCADE ON UPDATE CASCADE
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Accommodation_Comments (
                                Accommodation_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Accommodation_ID INTEGER REFERENCES Accommodation(Accommodation_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Accommodation_Comment_Text CHAR(500) NOT NULL
                    );"""
        cursor.execute(query)




        query = """CREATE TABLE IF NOT EXISTS City_Comments (
                                City_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                City_ID INTEGER REFERENCES City(City_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                City_Comment_Text CHAR(500) NOT NULL
                    );"""
        cursor.execute(query)



        query = """CREATE TABLE IF NOT EXISTS Team (
                                Team_ID SERIAL PRIMARY KEY NOT NULL,
                                Team_Name CHAR(50) NOT NULL,
                                Team_CountryID INT REFERENCES Country (Country_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Team_Total_Points INT DEFAULT 0
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Player (
                                Player_ID SERIAL PRIMARY KEY NOT NULL,
                                Player_Name CHAR(50) NOT NULL,
                                Player_TeamID INT REFERENCES Team (Team_ID) ON DELETE CASCADE ON UPDATE CASCADE
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Player_Comments (
                                Player_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Player_ID INTEGER REFERENCES Player(Player_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                PLayer_Comment_Text CHAR(500) NOT NULL
                    );"""
        cursor.execute(query)

        query = """INSERT INTO Player_Comments (Player_ID, PLayer_Comment_Text) VALUES (2,'ismail bir tuhaf adamdır')"""


        query = """CREATE TABLE IF NOT EXISTS Tournament (
                                Tournament_ID SERIAL PRIMARY KEY NOT NULL,
                                Tournament_Name CHAR(50) NOT NULL,
                                Tournament_CityID INT REFERENCES City (City_ID) ON DELETE CASCADE ON UPDATE CASCADE
                    );"""
        cursor.execute(query)


        query = """CREATE TABLE IF NOT EXISTS Team_Comments (
                                Team_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Team_ID INTEGER REFERENCES Team(Team_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Team_Comment_Text CHAR(500) NOT NULL
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Tournament_Comments (
                                Tournament_Comment_ID SERIAL PRIMARY KEY NOT NULL,
                                Tournament_ID INTEGER REFERENCES Tournament(Tournament_ID) ON DELETE CASCADE ON UPDATE CASCADE,
                                Tournament_Comment_Text CHAR(500) NOT NULL
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Place (
                                Place_ID SERIAL PRIMARY KEY NOT NULL,
                                Place_Name CHAR(50) NOT NULL
                    );"""
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Author (
                                Author_Student_ID INT PRIMARY KEY NOT NULL,
                                Author_Name CHAR(50) NOT NULL,
                                Author_Work_Description CHAR(500) NOT NULL
                    );
                    INSERT INTO Author (Author_Student_ID, Author_Name, Author_Work_Description) VALUES (150110018, 'Alper', 'Tournament, Tournament_Comment, Author');
                    INSERT INTO Author (Author_Student_ID, Author_Name, Author_Work_Description) VALUES (150120251, 'Cem', 'Team, Team_Comment, Admin Table');
                    INSERT INTO Author (Author_Student_ID, Author_Name, Author_Work_Description) VALUES (150110047, 'Tunahan', 'City, Country, Accommodation');
                    INSERT INTO Author (Author_Student_ID, Author_Name, Author_Work_Description) VALUES (150110023, 'Emre', 'Place');
                    INSERT INTO Author (Author_Student_ID, Author_Name, Author_Work_Description) VALUES (150110004, 'Ismail', 'Player, Manager, Admin Authorization');
                    """
        cursor.execute(query)

        query = """CREATE TABLE IF NOT EXISTS Admin (
                                Admin_ID SERIAL PRIMARY KEY NOT NULL,
                                Admin_Username CHAR(50) NOT NULL,
                                Admin_Password CHAR(50) NOT NULL
                    );"""
        cursor.execute(query)

        connection.commit()
    return redirect(url_for('home_page'))


@app.route('/count')
def counter_page():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()

        query = "UPDATE COUNTER SET N = N + 1"
        cursor.execute(query)
        connection.commit()

        query = "SELECT N FROM COUNTER"
        cursor.execute(query)
        count = cursor.fetchone()[0]
    return "This page was accessed %d times." % count

@app.route('/city')
def city_page():
    with dbapi2.connect(app.config['dsn']) as connection:
        cursor = connection.cursor()
        query  = "SELECT city_id FROM CITY "
        cursor.execute(query)
        count = cursor.fetchone()[0]
    return "This page was accessed %d times." % count



if __name__ == '__main__':
    VCAP_APP_PORT = os.getenv('VCAP_APP_PORT')
    if VCAP_APP_PORT is not None:
        port, debug = int(VCAP_APP_PORT), False
    else:
        port, debug = 5000, True

    VCAP_SERVICES = os.getenv('VCAP_SERVICES')
    if VCAP_SERVICES is not None:
        app.config['dsn'] = get_elephantsql_dsn(VCAP_SERVICES)
    else:
        app.config['dsn'] = """dbname=itucsdb host=localhost port=54321 user=vagrant password=vagrant"""

    app.run(host='0.0.0.0', port=port, debug=debug)
