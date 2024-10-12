from flask import Flask

app = Flask(__name__)

@app.route('/')
def docker_test():
    return 'Docker and Flask are working!'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3001)
