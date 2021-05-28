from flask import Flask
import json as j

app = Flask(__name__)



@app.route("/")
def home():
    return "There is no home page"

@app.route("/<name>")
def get_page(name):
    data = ""
    try:
        f = open("DB\\my_trivia_%s" %name + "_room.json")
        content = f.read()
        f.close()
        data = content
    except Exception as e:
        try:
            f.close()
        except Exception as er:
            pass
        data = "The error is: " + e.__str__()
    return data



if __name__ == '__main__':
    app.run()