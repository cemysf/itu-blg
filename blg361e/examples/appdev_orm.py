from sqlalchemy import create_engine
from sqlalchemy import MetaData
from sqlalchemy import Column, Table
from sqlalchemy import Float, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import mapper
from sqlalchemy.orm import relationship
from sqlalchemy.orm import sessionmaker


#=============================================
# CLASSES
#=============================================

class Person:
    def __init__(self, name):
        self.name = name


class Movie:
    def __init__(self, title, year=None, score=None, votes=None):
        self.title = title
        self.yr = year
        self.score = score
        self.votes = votes


#=============================================
# DATABASE SETUP
#=============================================

uri = 'postgres://vagrant:vagrant@localhost:5432/itucsdb'
# engine = create_engine(uri, echo=True)
engine = create_engine(uri)

metadata = MetaData()

person_table = Table('Person', metadata,
                     Column('id', Integer, primary_key=True),
                     Column('name', String(40)))

movie_table = Table('Movie', metadata,
                    Column('id', Integer, primary_key=True),
                    Column('title', String(80), nullable=False),
                    Column('yr', Integer),
                    Column('score', Float),
                    Column('votes', Integer),
                    Column('directorid', Integer, ForeignKey('Person.id')))

casting_table = Table('Casting', metadata,
                      Column('movieid', Integer, ForeignKey('Movie.id'),
                             primary_key=True),
                      Column('actorid', Integer, ForeignKey('Person.id'),
                             primary_key=True),
                      Column('ord', Integer))


#=============================================
# MAPPER SETUP
#=============================================

#mapper(Person, person_table,
#       properties={
#           'directed': relationship(Movie, backref='director'),
#           'acted': relationship(Movie, backref='cast',
#                                 secondary=casting_table)
#       })
#
#mapper(Movie, movie_table)

mapper(Person, person_table)

mapper(Movie, movie_table,
       properties={
           'director': relationship(Person, backref='directed'),
           'cast': relationship(Person, backref='acted',
                                secondary=casting_table)
       })


#=============================================
# CREATE TABLES
#=============================================

metadata.create_all(bind=engine)


#=============================================
# CREATE SESSION
#=============================================

Session = sessionmaker(bind=engine)
session = Session()

movie = Movie('Casablanca', year=1942)
session.add(movie)
session.commit()

movie.votes = 23283
session.commit()

session.delete(movie)
session.commit()


#=============================================
# INSERT DATA
#=============================================

movie_data = [
    {'title': "Usual Suspects",
     'year': 1995,
     'score': 8.7,
     'votes': 35027,
     'director': "Bryan Singer",
     'cast': ["Kevin Spacey", "Gabriel Byrne"]},
    {'title': "Being John Malkovich",
     'year': 1999,
     'score': 8.3,
     'votes': 13809,
     'director': "Spike Jonze",
     'cast': ["Cameron Diaz", "John Cusack", "John Malkovich"]},
    {'title': "Sleepy Hollow",
     'year': 1999,
     'score': 7.5,
     'votes': 10514,
     'director': "Tim Burton",
     'cast': ["Johnny Depp", "Christina Ricci"]},
    {'title': "Three Kings",
     'year': 1999,
     'score': 7.7,
     'votes': 10319,
     'director': "David O'Russell",
     'cast': ["George Clooney", "Spike Jonze"]},
    {'title': "Ed Wood",
     'year': 1994,
     'score': 7.8,
     'votes': 6587,
     'director': "Tim Burton",
     'cast': ["Johnny Depp"]}
]

persons = {}
for item in movie_data:
    person_names = [item['director']] + item['cast']
    for name in person_names:
        if name not in persons:
            person = Person(name)
            session.add(person)
            session.commit()
            persons[name] = person

for item in movie_data:
    movie = Movie(item['title'], year=item['year'], score=item['score'],
                  votes=item['votes'])
    movie.director = persons[item['director']]
    movie.cast = []
    for name in item['cast']:
        movie.cast.append(persons[name])
    session.add(movie)
    session.commit()


#=============================================
# QUERY EXAMPLES
#=============================================

print('MOVIES AND SCORES')
print('=================')
for movie in session.query(Movie):
    print('{}: {} ({} votes)'.format(movie.title, movie.score, movie.votes))

print()
print('MOVIES AND YEARS')
print('================')
for movie in session.query(Movie):
    print('{}: {}'.format(movie.title, movie.yr))

print()
print('ORDERED MOVIES')
print('==============')
for movie in session.query(Movie).order_by(Movie.yr):
    print('{} {}'.format(movie.yr, movie.title))

print()
print('MOVIES IN 1999')
print('==============')
for movie in session.query(Movie).filter_by(yr=1999):
    print('{}: {} ({} votes)'.format(movie.title, movie.score, movie.votes))

print()
print('MOVIES AND DIRECTORS')
print('====================')
for movie in session.query(Movie):
    print('{}: {}'.format(movie.title, movie.director.name))

print()
print('PEOPLE AND MOVIES THEY DIRECTED')
print('===============================')
for person in session.query(Person):
    print('{}:'.format(person.name))
    for movie in person.directed:
        print('  {}'.format(movie.title))

print()
print('MOVIES AND CAST')
print('===============')
for movie in session.query(Movie):
    print('{}:'.format(movie.title))
    for person in movie.cast:
        print('  {}'.format(person.name))

print()
print('PEOPLE AND MOVIES THEY ACTED IN')
print('===============================')
for person in session.query(Person):
    print('{}:'.format(person.name))
    for movie in person.acted:
        print('  ', movie.title)
