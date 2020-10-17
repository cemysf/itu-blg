import datetime
from flask import Flask
from flask import render_template


from movie import Movie

app = Flask(__name__)


@app.route('/') 
def home_page():
    now = datetime.datetime.now()
    return render_template('home.html', current_time=now.ctime())
    
    
@app.route('/movies') 
def movies_page():
    movie1 = Movie('The Shining', year=1980)
    movie2 = Movie('Barton Fink', year=1991)
    movies = [(1, movie1), (2, movie2)]
    now = datetime.datetime.now()
    return render_template('movies.html', movies=movies, current_time=now.ctime())



if __name__ == '__main__': 
    app.run(host='0.0.0.0', port=5000)

