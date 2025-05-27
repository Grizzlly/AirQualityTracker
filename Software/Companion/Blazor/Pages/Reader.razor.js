let map
let heatmap
let dataPoints = []
let markers = []

function createSVGMarker(color, outerR, innerR) {
    const div = document.createElement("div");
    div.innerHTML = `
        <svg width="${outerR * 3}" height="${outerR * 3}" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <circle cx="12" cy="12" r="${outerR}" fill="${color}" stroke="#FFFFFF" stroke-width="2"/>
            <circle cx="12" cy="12" r="${innerR}" fill="#FFFFFF"/>
        </svg>
    `;
    return div;
}


export async function initMap(lat, lng) {
    // Initialize the map
    const { LatLng } = await google.maps.importLibrary("core");
    const { Map } = await google.maps.importLibrary("maps");
    const { HeatmapLayer } = await google.maps.importLibrary("visualization");
    const { AdvancedMarkerElement } = await google.maps.importLibrary("marker");

    map = new Map(document.getElementById("readerMap"), {
        zoom: 15,
        center: new LatLng(lat, lng),
        mapTypeId: "roadmap",
        mapId: "DEMO_MAP_ID"
    })
    // Add current location marker
    const currentLocationMarker = new AdvancedMarkerElement({
        position: new LatLng(lat, lng),
        map: map,
        title: "Current Location",
        content: createSVGMarker("#3B82F6", 8, 3)
    })

    // Initialize heatmap
    heatmap = new HeatmapLayer({
        data: [],
        map: map,
        radius: 50,
        opacity: 0.8,
    })

    // Set heatmap gradient (green to red based on AQI)
    const gradient = [
        "rgba(0, 255, 255, 0)",
        "rgba(0, 255, 255, 1)",
        "rgba(0, 191, 255, 1)",
        "rgba(0, 127, 255, 1)",
        "rgba(0, 63, 255, 1)",
        "rgba(0, 0, 255, 1)",
        "rgba(0, 0, 223, 1)",
        "rgba(0, 0, 191, 1)",
        "rgba(0, 0, 159, 1)",
        "rgba(0, 0, 127, 1)",
        "rgba(63, 0, 91, 1)",
        "rgba(127, 0, 63, 1)",
        "rgba(191, 0, 31, 1)",
        "rgba(255, 0, 0, 1)",
    ]

    heatmap.set("gradient", gradient)
}

export async function addDataPoint(lat, lng, aqi, color) {
    const { LatLng } = await google.maps.importLibrary("core");
    const { AdvancedMarkerElement } = await google.maps.importLibrary("marker");
    // Create weighted point for heatmap
    const weightedLocation = {
        location: new LatLng(lat, lng),
        weight: Math.max(1, aqi / 50), // Normalize AQI to weight
    }

    dataPoints.push(weightedLocation)

    // Update heatmap data
    heatmap.setData(dataPoints)

    // Add a small marker for this data point
    const marker = new AdvancedMarkerElement({
        position: new LatLng(lat, lng),
        map: map,
        title: `AQI: ${aqi}`,
        content: createSVGMarker("#3B82F6", 8, 3),
    })

    markers.push(marker)

    // Keep only last 50 markers to avoid clutter
    if (markers.length > 50) {
        const oldMarker = markers.shift()
        oldMarker.setMap(null)
    }

    // Keep only last 100 data points for performance
    if (dataPoints.length > 100) {
        dataPoints.shift()
    }
}

export function clearHeatmap() {
    dataPoints = []
    heatmap.setData([])

    // Clear all markers
    markers.forEach((marker) => marker.setMap(null))
    markers = []
}
