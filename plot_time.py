import matplotlib.pyplot as plt
import json

x = []
index = 1
times = []

dictionary = json.load(open('results_time.json', 'r'))
print(type(dictionary))
print(dictionary["results"])
print(type(dictionary["results"]))
for i in dictionary["results"]:
    # print(i["time"])
    x.append(index)
    index = index + 1
    times.append(i["time"])
print(x)
print(times)
print(len(x))
print("total time: " + str(times[-1]-times[0]) + " second")
print("total number: " + str(x[-1]-x[0]))
print("average processing time for one image: " + str((times[-1]-times[0])/(x[-1]-x[0])) + " second")
# sleep(5)
# xAxis = [key for key, value in dictionary[results].items()]
# print(xAxis)
# yAxis = [value for key, value in dictionary.items()]
plt.grid(True)

## LINE GRAPH ##
plt.plot(x,times, color='maroon', marker='.')
plt.xlabel('image number')
plt.ylabel('accumulated time (second)')

## BAR GRAPH ##
# fig = plt.figure()
# plt.bar(xAxis,yAxis, color='maroon')
# plt.xlabel('variable')
# plt.ylabel('value')

plt.show()