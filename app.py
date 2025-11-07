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
        ("ct", ctypes.c_int),
    ]

class Vec(ctypes.Structure):
    _fields_ = [
        ("data", ctypes.POINTER(Gcq)),
        ("size", ctypes.c_size_t),
        ("capacity", ctypes.c_size_t)
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
    clib.call_FCFS.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
    clib.call_FCFS.restype = None
    n = len(ats)
    arr = (Process*n)()

    clib.create_vector.argtypes = None
    clib.create_vector.restype = ctypes.POINTER(Vec)

    gcq_ptr = clib.create_vector()

    for i in range(n):
        arr[i].id = i
        arr[i].at = ats[i]
        arr[i].burst = bursts[i]
        arr[i].priority = prts[i]

    clib.call_FCFS(arr, gcq_ptr, n)

    v = gcq_ptr.contents
    gcq = [(v.data[i].id, v.data[i].ct) for i in range(v.size)]

    clib.free_mem.argtypes = [ctypes.POINTER(Vec)]
    clib.free_mem(gcq_ptr)

    result = []
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

    return {"result": result, "gcq" : gcq}

@app.post("/sjf")
async def sjf(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in sjf")
    clib.call_SJF.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
    clib.call_SJF.restype = None
    n = len(ats)
    arr = (Process*n)()

    clib.create_vector.argtypes = None
    clib.create_vector.restype = ctypes.POINTER(Vec)

    gcq_ptr = clib.create_vector()

    for i in range(n):
        arr[i].id = i
        arr[i].at = ats[i]
        arr[i].burst = bursts[i]
        arr[i].priority = prts[i]

    clib.call_SJF(arr, gcq_ptr, n)

    v = gcq_ptr.contents
    gcq = [(v.data[i].id, v.data[i].ct) for i in range(v.size)]

    clib.free_mem.argtypes = [ctypes.POINTER(Vec)]
    clib.free_mem(gcq_ptr)

    result = []
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

    return {"result": result, "gcq" : gcq}