import ctypes
from typing import List
from fastapi import FastAPI, Body

app = FastAPI(title="cpu-scheduler-app")

clib = ctypes.CDLL('./c_file.so')

class Process(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_int),
        ("at", ctypes.c_int),
        ("ct", ctypes.c_int),
        ("wt", ctypes.c_int),
        ("tat", ctypes.c_int),
        ("burst", ctypes.c_int),
        ("rt", ctypes.c_int),
        ("priority", ctypes.c_int),
    ]

class Gcq(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_int),
        ("ct", ctypes.c_int), #elapsed time
    ]

@app.get("/")
async def root():
    return {"status": "ok", "message": "Space is running"}

@app.post("/fcfs")
async def fcfs(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in fcfs")
    clib.FCFS.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Gcq), ctypes.c_int)
    clib.FCFS.restype = None
    n = len(ats)
    arr = (Process*n)()
    gcq = (Gcq*n)()

    for i in range(n):
        arr[i].id = i
        arr[i].at = ats[i]
        arr[i].burst = bursts[i]
        arr[i].priority = prts[i]

    clib.call_FCFS(arr, gcq, n)

    result = []
    gcq_ = []
    for p in arr:
        result.append({
            "id": p.id,
            "at": p.at,
            "burst": p.burst,
            "priority": p.priority,
            "ct": p.ct,
            "wt": p.wt,
            "tat": p.tat,
            "rt": p.rt,
        })

    for p in gcq:
        gcq_.append({
            "id" : p.id,
            "ct" : p.ct
        })

    return {"result": result, "gcq" : gcq_}