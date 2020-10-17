import datetime
from flask import Flask
from flask import render_template

from movie import Movie
from store import Store

app = Flask(__name__)


@app.route('/') 
def home_page():
    now = datetime.datetime.now()
    return render_template('home.html', current_time=now.ctime())
    
    
@app.route('/movies') 
def movies_page():
    now = datetime.datetime.now()
    movies = app.store.get_movies()
    return render_template('movies.html', movies=movies, current_time=now.ctime())

@app.route('/movie/<int:key>') 
def movie_page(key):
    now = datetime.datetime.now()
    movie = app.store.get_movie(key)
    return render_template('movie.html', movie=movie,
                           current_time=now.ctime())
    
    


if __name__ == '__main__': 
    app.store = Store()
    app.store.add_movie(Movie('The Shining', year=1980)) 
    app.store.add_movie(Movie('Barton Fink', year=1991))
    app.run(host='0.0.0.0', port=5000)

