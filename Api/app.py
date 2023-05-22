import os
from fastapi import FastAPI, Request, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import Response, JSONResponse
import motor.motor_asyncio
from bson import ObjectId
import pydantic
import requests
from dotenv import load_dotenv
from datetime import datetime
load_dotenv()

app= FastAPI()

origins=[
    "http://localhost:8000",
    "https://simple-smart-hub-client.netlify.app",
    "https://rivproject.onrender.com/"
    ]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

client= motor.motor_asyncio.AsyncIOMotorClient(os.getenv("mongo_db_url"))
db= client.smat_control

pydantic.json.ENCODERS_BY_TYPE[ObjectId]=str

def getsunset_time():
 [ "https://simple-smart-hub-client.netlify.app"]
response= requests.get("https://api.sunrise-sunset.org/json?lat=q7.7936&lng=-76.7936")
data= response.json()

sunset= data["results"]["sunset"]
sunset_time= datetime.datetime.strptime(sunset, "%I:%M:%S %p")
 return sunset_time

@app.get("/api/state")
async def get_parameter():
    temperature= await db["control_system"].find().sort("date").to_list(999)

    """ fan= False"""
    """ light= False"""

    return temperature

@app.put("/api/getparam", status_code=201)
async def get_temperature(request:Request):
    temp_object= await request.json()
    
    user_temp= await db["control_system"].insert_one(temp_object)
    input_temp= await db["control_system"].find_one({"_id":user_temp.inserted_id})

    return input_temp

@app.get("/graph")
async def get_parameter(request: Request):
    n = int(request.query_params.get('size', 10))
    sensor_input= await db["data_input"].find().to_list(n)
    
    presence= [param["presence"] for param in sensor_input]
    temperatures=[param["temperature"] for param in sensor_input]
    datetimes= [param["datetime"] for param in sensor_input]

    output=[]
    if temperatures and presence and datetimes:
        output.append({
            "temperature": temperatures,
            "presence": presence,
            "datetime": datetimes
            })
        
    while len(output) < n:
        output.append({
            "temperature": 1.0,
            "presence": False,
            "datetime": datetime.now().time()
        })

    return output

@app.put("/settings", status_code=201)
async def create_parameter(request:Request):
    parameter= await request.json()
    global temp
    temp= parameter["user_temp"]
    global light
    light= parameter["user_light"]
    global duration_time
    duration_time= parameter["light_duration"]

    if light=="sunset":
        global light_preference
        light_preference=getsunset_time()
    else: light_preference= datetime.strptime(light, "%H:%M:%S")

    duration_time= light_preference+datetime (duration_time)

    user_data={
        "user_temp": temp,
        "user_light": str(light_preference.time()),
        "light_time_off":str(duration_time.time())
    }
    user_preference= await db["control_system"].insert_one(user_data)
    input_preference= await db["control_system"].find_one({"_id":user_preference.inserted_id})

    return input_preference
    
    
