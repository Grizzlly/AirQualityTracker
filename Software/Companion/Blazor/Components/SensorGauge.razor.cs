using Microsoft.AspNetCore.Components;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Companion.Blazor.Components;

public partial class SensorGauge : ComponentBase
{
    private string GetProgressColor() => TType switch
    {
        SensorType.Temperature => Value switch
        {
            < 10 => "#3b82f6",
            //blue
            < 25 => "#10b981",
            //green
            < 35 => "#f59e0b",
            //yellow
            _ => "#ef4444" // red
        },
        SensorType.Humidity => Value switch
        {
            < 30 => "#ef4444",
            //red(too dry)

            < 60 => "#10b981",
            //green(good)

            < 80 => "#f59e0b",
            //yellow(high)
            _ => "#ef4444" // red(too humid)
        },
        SensorType.Pressure => "#8b5cf6",
        //purple
        SensorType.GasResistance => "#06b6d4",
        //cyan
        SensorType.AirQuality => Value switch
        {
            <= 50 => "#10b981",
            //green
            <= 100 => "#f59e0b",
            //yellow
            <= 150 => "#f97316",
            //orange
            _ => "#ef4444" // red

        },
        _ => "#6b7280" // gray
    };

    private string GetStatus() => TType switch
    {
        SensorType.Temperature => Value switch
        {
            < 10 => "Cold",
            < 18 => "Cool",
            < 25 => "Comfortable",
            < 30 => "Warm",
            _ => "Hot"
        },
        SensorType.Humidity => Value switch
        {
            < 30 => "Too Dry",
            < 40 => "Dry",
            < 60 => "Comfortable",
            < 70 => "Humid",
            _ => "Too Humid"
        },
        SensorType.Pressure => Value switch
        {
            < 1000 => "Low",
            < 1020 => "Normal",
            _ => "High"
        },
        SensorType.GasResistance => Value switch
        {
            < 50000 => "Poor",
            < 100000 => "Fair",
            < 200000 => "Good",
            _ => "Excellent"
        },
        SensorType.AirQuality => Value switch
        {
            <= 50 => "Good",
            <= 100 => "Moderate",
            <= 150 => "Unhealthy for Sensitive",
            <= 200 => "Unhealthy",
            <= 300 => "Very Unhealthy",
            _ => "Hazardous"
        },
        _ => "Unknown"
    };
}
