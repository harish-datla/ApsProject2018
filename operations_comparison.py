import plotly.plotly as py
import plotly.graph_objs as go
import pandas as pd
import plotly
plotly.tools.set_credentials_file(username='harishkumardatla', api_key='m91sO30XjdR7bPVyXQQO')

data = pd.read_csv('quick_insert_time.csv', header=None,low_memory=False, encoding="utf-8-sig",  delimiter=',')

dataPd = pd.DataFrame(data = data)

print dataPd.columns

print data.columns

height =dataPd[1].tolist()

nodes = dataPd[0].tolist()

# Create and style traces
trace0 = go.Scatter(
    x = nodes,
    y = height,
    name = 'Quick Insert',
    line = dict(
        color = ('rgb(205, 12, 24)'),
        width = 4)
)

data = pd.read_csv('rotate_insert_time.csv', header=None,low_memory=False, encoding="utf-8-sig",  delimiter=',')

dataPd = pd.DataFrame(data = data)

print dataPd.columns

print data.columns

height =dataPd[1].tolist()

nodes = dataPd[0].tolist()

trace1 = go.Scatter(
    x = nodes,
    y = height,
    name = 'Rotate Insert',
    line = dict(
        color = ('rgb(15, 12, 190)'),
        width = 4)
)

data = pd.read_csv('rotate_delete_time.csv', header=None,low_memory=False, encoding="utf-8-sig",  delimiter=',')

dataPd = pd.DataFrame(data = data)

print dataPd.columns

print data.columns

height =dataPd[1].tolist()

nodes = dataPd[0].tolist()

trace2 = go.Scatter(
    x = nodes,
    y = height,
    name = 'Rotate Delete',
    line = dict(
        color = ('rgb(15, 200, 9)'),
        width = 4)
)

data = [trace0, trace1, trace2]

# Edit the layout
layout = dict(title = 'Performance Comparison',
              xaxis = dict(title = 'Size'),
              yaxis = dict(title = 'Time(micro seconds)'),
              )

fig = dict(data=data, layout=layout)
py.iplot(fig, filename='styled-line')