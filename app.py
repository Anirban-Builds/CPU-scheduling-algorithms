import ctypes
from typing import List
from fastapi import FastAPI, Body
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI(title="cpu-scheduler-app")
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# clib = ctypes.CDLL('./c_file.so')
clib = ctypes.CDLL('./c_file.dll')

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
        ("complete", ctypes.c_bool)
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

clib.create_vector.argtypes = None
clib.create_vector.restype = ctypes.POINTER(Vec)

clib.free_mem.argtypes = [ctypes.POINTER(Vec)]
clib.free_mem.restype = None

clib.call_FCFS.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_FCFS.restype = None

clib.call_SJF.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_SJF.restype = None

clib.call_LJF.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_LJF.restype = None

clib.call_SRTF.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_SRTF.restype = None

clib.call_LRTF.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_LRTF.restype = None

clib.call_NPPS.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_NPPS.restype = None

clib.call_PPS.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_PPS.restype = None

clib.call_HRRN.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec), ctypes.c_int)
clib.call_HRRN.restype = None

clib.call_RR.argtypes = (ctypes.POINTER(Process), ctypes.POINTER(Vec),
                               ctypes.c_int, ctypes.c_int)
clib.call_RR.restype = None

def fill_arr(arr, ats, bursts, prts, n):
    for i in range(n):
        arr[i].id = i
        arr[i].at = ats[i]
        arr[i].burst = bursts[i]
        arr[i].priority = prts[i]

def fill_res(arr):
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
    return result

def fill_vec(gcq_ptr, n):
    v = gcq_ptr.contents
    gcq = [(v.data[i].id, v.data[i].ct) for i in range(n)]
    clib.free_mem(gcq_ptr)
    return gcq

@app.get("/")
async def root():
    return {"status": "ok", "message": "Space is running"}

@app.post("/fcfs")
async def fcfs(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in fcfs")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()
    fill_arr(arr, ats, bursts, prts, n)

    clib.call_FCFS(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/sjf")
async def sjf(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in sjf")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_SJF(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)
    return {"result": result, "gcq" : gcq}

@app.post("/ljf")
async def ljf(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in ljf")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_LJF(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/srtf")
async def srtf(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in srtf")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_SRTF(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/lrtf")
async def lrtf(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in lrtf")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_LRTF(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/npps")
async def npps(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in npps")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_NPPS(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/pps")
async def pps(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in pps")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_PPS(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/hrrn")
async def hrrn(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...)
               ):
    print("here in hrrn")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_HRRN(arr, gcq_ptr, n)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}

@app.post("/rr")
async def rr(ats : List[int] = Body(...),
               bursts : List[int] = Body(...),
               prts : List[int] = Body(...),
               q : int = Body(...)
               ):
    print("here in rr")
    n = len(ats)
    arr = (Process*n)()

    gcq_ptr = clib.create_vector()

    fill_arr(arr, ats, bursts, prts, n)

    clib.call_RR(arr, gcq_ptr, n, q)

    gcq = fill_vec(gcq_ptr, n)
    result = fill_res(arr)

    return {"result": result, "gcq" : gcq}