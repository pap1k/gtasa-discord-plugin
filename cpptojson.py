import json, re

cppdata = open("cpplocations.txt", 'r', encoding="utf-8").read()
outdata = {
    "locations": []
}

for line in cppdata.split("\n"):
    line = line.strip()
    numbers = re.findall(r",\s*([-+]?(?:\d*\.*\d+))", line)
    name = re.findall(r"\"(.+)\"", line)[0]

    loc = {"name": name, "pos": list(map(float, numbers))}

    outdata['locations'].append(loc)

open("locations.json", "w").write(json.dumps(outdata))
