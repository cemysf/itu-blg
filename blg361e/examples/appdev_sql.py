import psycopg2 as dbapi2


dsn = """user='vagrant' password='vagrant'
         host='localhost' port=5432 dbname='itucsdb'"""


#=============================================
# CREATE THE TABLES
#=============================================

try:
    connection = dbapi2.connect(dsn)
    cursor = connection.cursor()
    statement = """CREATE TABLE PERSON (
        ID SERIAL PRIMARY KEY,
        NAME VARCHAR(40) UNIQUE NOT NULL
    )"""
    cursor.execute(statement)
    connection.commit()
    cursor.close()
except dbapi2.DatabaseError:
    connection.rollback()
finally:
    connection.close()


with dbapi2.connect(dsn) as connection:
    cursor = connection.cursor()
    statement = """CREATE TABLE MOVIE (
        ID SERIAL PRIMARY KEY,
        TITLE VARCHAR(80),
        YR NUMERIC(4),
        SCORE FLOAT,
        VOTES INTEGER DEFAULT 0,
        DIRECTORID INTEGER REFERENCES PERSON (ID)
    )"""
    cursor.execute(statement)
    cursor.close()


with dbapi2.connect(dsn) as connection:
    with connection.cursor() as cursor:
        statement = """CREATE TABLE CASTING (
            MOVIEID INTEGER REFERENCES MOVIE (ID),
            ACTORID INTEGER REFERENCES PERSON (ID),
            ORD INTEGER,
            PRIMARY KEY (MOVIEID, ACTORID)
        )"""
        cursor.execute(statement)


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

person_ids = {}
with dbapi2.connect(dsn) as connection:
    with connection.cursor() as cursor:
        for item in movie_data:
            person_names = [item['director']] + item['cast']
            for name in person_names:
                if name not in person_ids:
                    statement = """INSERT INTO PERSON (NAME) VALUES (%s)
                                   RETURNING id"""
                    cursor.execute(statement, (name,))
                    connection.commit()
                    person_id = cursor.fetchone()[0]
                    person_ids[name] = person_id

with dbapi2.connect(dsn) as connection:
    with connection.cursor() as cursor:
        for item in movie_data:
            statement = """
                INSERT INTO MOVIE (TITLE, YR, SCORE, VOTES, DIRECTORID)
                           VALUES (%(title)s, %(year)s, %(score)s, %(votes)s,
                                   %(directorid)s)
                RETURNING id
            """
            item['directorid'] = person_ids[item['director']]
            cursor.execute(statement, item)
            connection.commit()
            movie_id = cursor.fetchone()[0]

            for actor_ord, actor in enumerate(item['cast']):
                statement = """INSERT INTO CASTING (MOVIEID, ACTORID, ORD)
                                            VALUES (%s, %s, %s)"""
                cursor.execute(statement, (movie_id, person_ids[actor],
                                           actor_ord + 1))
                connection.commit()


#=============================================
# QUERY EXAMPLES
#=============================================

with dbapi2.connect(dsn) as connection:
    with connection.cursor() as cursor:
        print('MOVIES AND SCORES')
        print('=================')
        statement = """SELECT TITLE, SCORE, VOTES FROM MOVIE"""
        cursor.execute(statement)
        for row in cursor:
            title, score, votes = row
            print('{}: {} ({} votes)'.format(title, score, votes))

        print()
        print('MOVIES AND YEARS')
        print('================')
        statement = """SELECT TITLE, YR FROM MOVIE"""
        cursor.execute(statement)
        for title, year in cursor:
            print('{}: {}'.format(title, year))

        print()
        print('ORDERED MOVIES')
        print('==============')
        statement = """SELECT TITLE, YR FROM MOVIE ORDER BY YR ASC"""
        cursor.execute(statement)
        for title, yr in cursor:
            print('{} {}'.format(yr, title))

        print()
        print('MOVIES IN 1999')
        print('==============')
        statement = """SELECT TITLE, SCORE, VOTES FROM MOVIE
                        WHERE (YR = 1999)"""
        cursor.execute(statement)
        for title, score, votes in cursor:
            print('{}: {} ({} votes)'.format(title, score, votes))

        print()
        print('MOVIES AND DIRECTORS')
        print('====================')
        statement = """SELECT TITLE, NAME
                         FROM MOVIE JOIN PERSON
                           ON (MOVIE.DIRECTORID = PERSON.ID)"""
        cursor.execute(statement)
        for title, name in cursor:
            print('{}: {}'.format(title, name))

        print()
        print('PEOPLE AND MOVIES THEY DIRECTED')
        print('===============================')
        statement = """SELECT ID, NAME FROM PERSON"""
        cursor.execute(statement)
        people = cursor.fetchall()
        for person_id, name in people:
            statement = """SELECT TITLE FROM MOVIE
                            WHERE (DIRECTORID = %s)"""
            cursor.execute(statement, (person_id,))
            directed = cursor.fetchall()
            print('{}:'.format(name))
            for (title,) in directed:
                print('  {}'.format(title))

        print()
        print('MOVIES AND CAST')
        print('===============')
        statement = """SELECT ID, TITLE FROM MOVIE"""
        cursor.execute(statement)
        movies = cursor.fetchall()
        for movie_id, title in movies:
            statement = """SELECT NAME
                             FROM PERSON JOIN CASTING
                                    ON (CASTING.ACTORID = PERSON.ID)
                            WHERE (MOVIEID = %s)"""
            cursor.execute(statement, (movie_id,))
            cast = cursor.fetchall()
            print('{}:'.format(title))
            for (name,) in cast:
                print('  {}'.format(name))

        print()
        print('PEOPLE AND MOVIES THEY ACTED IN')
        print('===============================')
        statement = """SELECT ID, NAME FROM PERSON"""
        cursor.execute(statement)
        people = cursor.fetchall()
        for person_id, name in people:
            statement = """SELECT TITLE
                             FROM MOVIE JOIN CASTING
                               ON (MOVIEID = MOVIE.ID)
                            WHERE (ACTORID = %s)"""
            cursor.execute(statement, (person_id,))
            acted = cursor.fetchall()
            print('{}:'.format(name))
            for (title,) in acted:
                print('  {}'.format(title))
