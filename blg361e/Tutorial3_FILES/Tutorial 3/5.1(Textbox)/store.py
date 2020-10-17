class Store:
    def __init__(self):
        self.movies = {}
        self.last_key = 0
        
    def add_movie(self, movie):
        self.last_key += 1 
        self.movies[self.last_key] = movie
        
    def delete_movie(self, key): 
        del self.movies[key]
        
    def get_movie(self, key): 
        return self.movies[key]

    def get_movies(self):
        return sorted(self.movies.items())