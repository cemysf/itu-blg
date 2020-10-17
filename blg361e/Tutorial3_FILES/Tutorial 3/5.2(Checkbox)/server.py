import datetime
from flask import Flask
from flask import redirect
from flask import render_template
from flask import request
from flask import url_for

from movie import Movie
from store import Store

app = Flask(__name__)


@app.route('/') 
def home_page():
    now = datetime.datetime.now()
    return render_template('home.html', current_time=now.ctime())
    
    
@app.route('/movies', methods=['GET', 'POST']) 
def movies_page():
    if request.method == 'GET':
        now = datetime.datetime.now() 
        movies = app.store.get_movies()
        return render_template('movies.html', movies=movies, current_time=now.ctime())
    elif 'movies_to_delete' in request.form:
        keys = request.form.getlist('movies_to_delete') 
        for key in keys:
            app.store.delete_movie(int(key)) 
        return redirect(url_for('movies_page'))
    else:
      title = request.form['title']
      year = request.form['year']
      movie = Movie(title, year)
      app.store.add_movie(movie)
      return redirect(url_for('movie_page', key=app.store.last_key))
      
      
@app.route('/movies/add') 
def movie_edit_page():
    now = datetime.datetime.now()
    return render_template('movie_edit.html', current_time=now.ctime())
      


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

