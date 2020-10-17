import datetime
from flask import Flask
from flask import render_template
app = Flask(__name__)


@app.route('/') 
def home_page():
    now = datetime.datetime.now()
    return render_template('home.html', current_time=now.ctime())
    
    
if __name__ == '__main__': 
    app.run(host='0.0.0.0', port=5000)

