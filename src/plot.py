import matplotlib.pyplot as plt

#Single Threaded Merge Sort
x1 = ["$10^2$","$10^3$","$10^4$","$10^5$","$5*10^5$","$10^6$"]
y1 = [0,0,8,90,353,730]

#Multi Threaded Merge Sort
x2 = ["$10^2$","$10^3$","$10^4$","$10^5$","$5*10^5$","$10^6$"]
y2 = [0,0,4,49,185,380]


#Single Threaded Quick Sort
x3 = ["$10^2$","$10^3$","$10^4$","$10^5$","$5*10^5$","$10^6$"]
y3 = [0,0,1,17,170,353]

#Multi Threaded Quick Sort
x4 = ["$10^2$","$10^3$","$10^4$","$10^5$","$5*10^5$","$10^6$"]
y4 = [0,0,0,10,130,251]


plt.plot(x1,y1,'*:b')
plt.plot(x2,y2,"or")
plt.plot(x1,y1,":",label="single threaded mergesort",color='blue')
plt.plot(x2,y2,label="multi threaded mergesort",color='red')

plt.plot(x3,y3,'*:g')
plt.plot(x4,y4,"om")
plt.plot(x3,y3,":",label="single threaded quicksort",color="green")
plt.plot(x4,y4,label="multi threaded quicksort",color="black") 


#adding legend
plt.legend(loc="upper left")

# naming the x-axis
plt.xlabel('Size of Array')

# naming the y-axis
plt.ylabel('Execution Time (m/s)')

plt.title('Quick Sort vs Merge Sort')

plt.grid()

plt.show()

plt.savefig('all__sort_comparison.png')



