import React, { useEffect, useState } from 'react';
import axios from 'axios';

import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';

const TemperaturesChart = () => {
  const [chartData, setChartData] = useState([]);

  const fetchTemperatures = async () => {
    try {
      const response = await axios.get('http://localhost:5000/temperaturas');
      const data = response.data;
      const formattedData = data.map(item => ({
        fecha: item.fecha_hora,
        temperatura: item.temp,
      }));
      setChartData(formattedData);
    } catch (error) {
      console.error('Error al obtener los datos de temperatura', error);
    }
  };
  const CustomizedLabel = ({ x, y, stroke, value, index, data }) => {
    return (
      <text x={x} y={y-10} dy={-4} fill={stroke} fontSize={10} textAnchor="middle">
        {`${data[index].temperatura}°C - ${data[index].fecha}`}
      </text>
    );
  };
  useEffect(() => {
    fetchTemperatures();
  }, []);

  return (
    <ResponsiveContainer width="100%" height={300}>
      <LineChart
        width={500}
        height={300}
        data={chartData}
        margin={{
          top: 5,
          right: 30,
          left: 20,
          bottom: 5,
        }}
      >
        <XAxis dataKey="name"  />
        <YAxis />
        <Tooltip  />
        <Legend />
        <Line type="monotone" dataKey="temperatura" stroke="#8884d8" activeDot={{ r: 8 }}  />
      </LineChart>
    </ResponsiveContainer>
  );
};

export default TemperaturesChart;
