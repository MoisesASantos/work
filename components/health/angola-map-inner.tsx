"use client"

import { MapContainer, TileLayer, Marker, Popup, useMap } from "react-leaflet"
import "leaflet/dist/leaflet.css"
import { Building2, Plus, Minus, LocateFixed, Pill, Stethoscope, Navigation, Maximize2, Minimize2, X, Layers } from "lucide-react"
import { type HealthFacility } from "./health-facility-card"
import Link from "next/link"
import { useState, useEffect } from "react"
import L from "leaflet"
import { Button } from "@/components/ui/button"

// Configuração de icones
const createIcon = (colorClass: string, IconComponent: any) => {
  return L.divIcon({
    className: "custom-leaflet-icon",
    html: `<div class="relative w-8 h-8 flex items-center justify-center -translate-x-1/2 -translate-y-[100%]">
      <div class="${colorClass} text-white p-2 rounded-full shadow-lg ring-2 ring-white">
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-4 h-4"><use href="#${IconComponent.name}" /></svg>
      </div>
      <div class="absolute -bottom-1 left-1/2 -translate-x-1/2 w-2 h-2 ${colorClass} rotate-45"></div>
    </div>`,
    iconSize: [32, 32],
    iconAnchor: [16, 32],
    popupAnchor: [0, -32],
  })
}

// Map styles
const MAP_STYLES = {
  // CartoDB Voyager é uma alternativa excelente e muito permissiva para mapas de ruas
  streets: "https://{s}.basemaps.cartocdn.com/rastertiles/voyager/{z}/{x}/{y}{r}.png",
  // Google Satellite (para uso em desenvolvimento, geralmente não bloqueia referers)
  satellite: "https://mt1.google.com/vt/lyrs=s&x={x}&y={y}&z={z}"
}

// Posições reais em Luanda
const markerPositions: Record<string, [number, number]> = {
  welwitschia: [-8.8143, 13.2302],
  maianga: [-8.8251, 13.2268],
  "hospital-militar": [-8.8315, 13.2424],
  "centro-saude-cazenga": [-8.8197, 13.2842],
  "clinica-sagrada": [-8.8123, 13.2384],
  "farmacia-central": [-8.8091, 13.2351],
  "posto-viana": [-8.9192, 13.3768],
}
const defaultPosition: [number, number] = [-8.8354, 13.2323] // Luanda center

export interface AngolaMapProps {
  facilities?: HealthFacility[]
  isFullscreen?: boolean
  onExitFullscreen?: () => void
  onEnterFullscreen?: () => void
}

const typeIcons = {
  farmacia: Pill,
  hospital: Building2,
  posto: Stethoscope,
}

const typeColors = {
  farmacia: "bg-blue-600",
  hospital: "bg-red-600",
  posto: "bg-green-600",
}

function CustomControls({ 
  mapStyle, 
  setMapStyle, 
  isFullscreen, 
  onEnterFullscreen, 
  onExitFullscreen 
}: { 
  mapStyle: "streets" | "satellite", 
  setMapStyle: (s: "streets" | "satellite") => void,
  isFullscreen: boolean,
  onEnterFullscreen?: () => void,
  onExitFullscreen?: () => void
}) {
  const map = useMap()

  return (
    <>
      <div className="absolute top-4 right-4 flex flex-col gap-2 z-[400]">
        <div className="bg-white shadow-lg rounded-xl overflow-hidden">
          <button 
            onClick={(e) => { e.preventDefault(); e.stopPropagation(); setMapStyle("streets"); }}
            className={`w-full px-3 py-2 text-xs font-medium flex items-center gap-2 transition-colors ${
              mapStyle === "streets" ? "bg-primary text-white" : "hover:bg-slate-50"
            }`}
          >
            <Layers className="w-4 h-4" />
            Mapa
          </button>
          <button 
            onClick={(e) => { e.preventDefault(); e.stopPropagation(); setMapStyle("satellite"); }}
            className={`w-full px-3 py-2 text-xs font-medium flex items-center gap-2 transition-colors ${
              mapStyle === "satellite" ? "bg-primary text-white" : "hover:bg-slate-50"
            }`}
          >
            <Layers className="w-4 h-4" />
            Satélite
          </button>
        </div>

        <div className="bg-white shadow-lg p-1 rounded-xl flex flex-col gap-1">
          <button onClick={() => map.zoomIn()} className="w-9 h-9 flex items-center justify-center hover:bg-slate-100 rounded-lg transition-colors">
            <Plus className="w-4 h-4" />
          </button>
          <div className="h-[1px] bg-slate-200 mx-2" />
          <button onClick={() => map.zoomOut()} className="w-9 h-9 flex items-center justify-center hover:bg-slate-100 rounded-lg transition-colors">
            <Minus className="w-4 h-4" />
          </button>
        </div>

        <button onClick={() => map.setView(defaultPosition, 13)} className="w-11 h-11 bg-white shadow-lg text-primary rounded-xl flex items-center justify-center hover:bg-slate-50 transition-colors">
          <LocateFixed className="w-5 h-5" />
        </button>

        {!isFullscreen && onEnterFullscreen && (
          <button onClick={onEnterFullscreen} className="w-11 h-11 bg-white shadow-lg rounded-xl flex items-center justify-center hover:bg-slate-50 transition-colors">
            <Maximize2 className="w-5 h-5" />
          </button>
        )}
        {isFullscreen && onExitFullscreen && (
          <button onClick={onExitFullscreen} className="w-11 h-11 bg-white shadow-lg rounded-xl flex items-center justify-center hover:bg-slate-50 transition-colors">
            <Minimize2 className="w-5 h-5" />
          </button>
        )}
      </div>
    </>
  )
}

export default function AngolaMapInner({ facilities = [], isFullscreen = false, onExitFullscreen, onEnterFullscreen }: AngolaMapProps) {
  const [mapStyle, setMapStyle] = useState<"streets" | "satellite">("streets")
  
  // Custom icons are made with divIcon natively in render below

  return (
    <section className={`flex-1 relative z-0 ${isFullscreen ? "fixed inset-0 z-50" : "h-full min-h-[400px]"}`}>
      {isFullscreen && (
        <button
          onClick={onExitFullscreen}
          className="absolute top-4 left-4 z-[500] bg-white shadow-lg rounded-xl p-3 hover:bg-slate-50 transition-colors"
        >
          <X className="w-5 h-5" />
        </button>
      )}

      {/* SVG definitions for our custom icons */}
      <svg width="0" height="0" className="hidden">
        <symbol id="Building2" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M6 22V4a2 2 0 0 1 2-2h8a2 2 0 0 1 2 2v18Z"/><path d="M6 12H4a2 2 0 0 0-2 2v6a2 2 0 0 0 2 2h2"/><path d="M18 9h2a2 2 0 0 1 2 2v9a2 2 0 0 1-2 2h-2"/><path d="M10 6h4"/><path d="M10 10h4"/><path d="M10 14h4"/><path d="M10 18h4"/></symbol>
        <symbol id="Pill" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="m10.5 20.5 10-10a4.95 4.95 0 1 0-7-7l-10 10a4.95 4.95 0 1 0 7 7Z"/><path d="m8.5 8.5 7 7"/></symbol>
        <symbol id="Stethoscope" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M4.8 2.3A.3.3 0 1 0 5 2H4a2 2 0 0 0-2 2v5a6 6 0 0 0 6 6v0a6 6 0 0 0 6-6V4a2 2 0 0 0-2-2h-1a.2.2 0 1 0 .3.3"/><path d="M8 15v1a6 6 0 0 0 6 6v0a6 6 0 0 0 6-6v-4"/><circle cx="20" cy="10" r="2"/></symbol>
      </svg>

      <MapContainer 
        center={defaultPosition} 
        zoom={13} 
        zoomControl={false}
        className="w-full h-full"
      >
        <TileLayer
          attribution='&copy; <a href="https://carto.com/">Carto</a> | &copy; Map data'
          url={MAP_STYLES[mapStyle]}
          maxZoom={19}
        />
        
        <CustomControls 
          mapStyle={mapStyle} 
          setMapStyle={setMapStyle} 
          isFullscreen={isFullscreen} 
          onEnterFullscreen={onEnterFullscreen}
          onExitFullscreen={onExitFullscreen}
        />

        {/* User Location */}
        <Marker 
          position={defaultPosition}
          icon={L.divIcon({
            className: "custom-leaflet-icon",
            html: `<div class="relative w-5 h-5 bg-blue-500 rounded-full border-2 border-white shadow-lg flex items-center justify-center">
                    <div class="absolute -inset-2 bg-blue-500/20 rounded-full animate-ping"></div>
                   </div>`,
            iconSize: [20, 20],
          })}
        >
          <Popup>Você está aqui</Popup>
        </Marker>

        {/* Facilities */}
        {facilities.map((facility) => {
          const position = markerPositions[facility.id] || [-8.8354, 13.2323]
          const Icon = typeIcons[facility.type]
          const bgColor = typeColors[facility.type]
          
          return (
            <Marker 
              key={facility.id}
              position={position}
              icon={createIcon(bgColor, Icon)}
            >
              <Popup className="rounded-xl overflow-hidden border-0 shadow-lg p-0 m-0">
                <div className="p-3 bg-white min-w-[200px]">
                  <h3 className="font-bold text-slate-900 leading-tight">{facility.name}</h3>
                  <div className="flex items-center gap-2 mt-2">
                    <span className="text-xs text-slate-500">{facility.distance}</span>
                    <Link href={`/instituicao/${facility.id}`} className="text-xs text-primary font-medium hover:underline">
                      Ver detalhes
                    </Link>
                  </div>
                </div>
              </Popup>
            </Marker>
          )
        })}
      </MapContainer>
    </section>
  )
}