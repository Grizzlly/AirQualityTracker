using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Companion.Blazor;

internal sealed class SensorReading
{
    public DateTime Timestamp { get; set; } = DateTime.Now;
    public double Latitude { get; set; }
    public double Longitude { get; set; }
    public short Temperature { get; set; }
    public short Humidity { get; set; }
    public short Pressure { get; set; }
    public short GasResistance { get; set; }
    public int AirQualityIndex { get; set; }

    public string GetAirQualityLevel()
    {
        return AirQualityIndex switch
        {
            <= 50 => "Good",
            <= 100 => "Moderate",
            <= 150 => "Unhealthy for Sensitive Groups",
            <= 200 => "Unhealthy",
            <= 300 => "Very Unhealthy",
            _ => "Hazardous"
        };
    }

    public string GetAirQualityColor()
    {
        return AirQualityIndex switch
        {
            <= 50 => "#00e400",
            <= 100 => "#ffff00",
            <= 150 => "#ff7e00",
            <= 200 => "#ff0000",
            <= 300 => "#8f3f97",
            _ => "#7e0023"
        };
    }
}
