import plotly
import plotly.graph_objs as go
import pandas as pd
import plotly
plotly.tools.set_credentials_file(username='harishkumardatla', api_key='m91sO30XjdR7bPVyXQQO')

data = pd.read_csv('height_vs_nodes_rbtree.csv', header=None,low_memory=False, encoding="utf-8-sig",  delimiter=',')

dataPd = pd.DataFrame(data = data)

print dataPd.columns

print data.columns

height =dataPd[0].tolist()

nodes = dataPd[1].tolist()

plotly.offline.plot({"data": [go.Scatter(x=nodes, y=height)],
                    "layout": go.Layout(title="Random BST Insertion")}, auto_open=True)