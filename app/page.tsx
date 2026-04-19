"use client"

import { useState } from "react"
import { Search, SlidersHorizontal, X, Clock, MapPin, Banknote, Star, Building2, Pill, Stethoscope, Check } from "lucide-react"
import { Input } from "@/components/ui/input"
import { Button } from "@/components/ui/button"
import { HealthFacilityCard, type HealthFacility } from "@/components/health/health-facility-card"
import { AngolaMap } from "@/components/health/angola-map"
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuTrigger,
  DropdownMenuCheckboxItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
} from "@/components/ui/dropdown-menu"

const healthFacilities: HealthFacility[] = [
  {
    id: "welwitschia",
    name: "Farmacia Welwitschia",
    type: "farmacia",
    address: "Talatona, Rua do MAT",
    rating: 4.8,
    reviews: "120+",
    distance: "1.2 km",
    status: "open",
  },
  {
    id: "maianga",
    name: "Apothecary Maianga",
    type: "farmacia",
    address: "Maianga, Av. Revolucao de Outubro",
    rating: 4.9,
    reviews: "340+",
    distance: "2.5 km",
    status: "24h",
    featured: true,
  },
  {
    id: "hospital-militar",
    name: "Hospital Militar Principal",
    type: "hospital",
    address: "Maianga, Luanda",
    rating: 4.6,
    reviews: "890+",
    distance: "3.1 km",
    status: "24h",
  },
  {
    id: "centro-saude-cazenga",
    name: "Centro de Saude do Cazenga",
    type: "posto",
    address: "Cazenga, Rua Principal",
    rating: 4.3,
    reviews: "156",
    distance: "4.0 km",
    status: "open",
  },
  {
    id: "clinica-sagrada",
    name: "Clinica Sagrada Esperanca",
    type: "hospital",
    address: "Talatona, Zona Economica",
    rating: 4.9,
    reviews: "1.2k",
    distance: "5.2 km",
    status: "24h",
    featured: true,
  },
  {
    id: "farmacia-central",
    name: "Farmacia Central",
    type: "farmacia",
    address: "Ingombota, Rua Rainha Ginga",
    rating: 4.5,
    reviews: "89",
    distance: "1.8 km",
    status: "closing-soon",
  },
  {
    id: "posto-viana",
    name: "Posto Medico de Viana",
    type: "posto",
    address: "Viana, Sector 12",
    rating: 4.2,
    reviews: "67",
    distance: "8.5 km",
    status: "open",
  },
]

// Main visible filters
const mainFilters = [
  { id: "24h", label: "Aberto 24H", icon: Clock },
  { id: "proximas", label: "Mais Proximas", icon: MapPin },
  { id: "baratas", label: "Mais Baratas", icon: Banknote },
  { id: "avaliadas", label: "Melhor Avaliadas", icon: Star },
]

// Additional filters in dropdown
const extraFilters = [
  { id: "abertas", label: "Abertas Agora" },
  { id: "estacionamento", label: "Com Estacionamento" },
  { id: "acessibilidade", label: "Acessivel" },
  { id: "plantao", label: "Em Plantao" },
]

const typeFilters = [
  { id: null, label: "Todos", icon: null },
  { id: "farmacia", label: "Farmacias", icon: Pill },
  { id: "hospital", label: "Hospitais", icon: Building2 },
  { id: "posto", label: "Postos Medicos", icon: Stethoscope },
]

export default function ExplorePage() {
  const [searchQuery, setSearchQuery] = useState("")
  const [activeFilter, setActiveFilter] = useState("proximas")
  const [selectedType, setSelectedType] = useState<string | null>(null)
  const [extraActiveFilters, setExtraActiveFilters] = useState<string[]>([])
  const [isMapFullscreen, setIsMapFullscreen] = useState(false)

  const toggleExtraFilter = (filterId: string) => {
    setExtraActiveFilters(prev => 
      prev.includes(filterId) 
        ? prev.filter(f => f !== filterId)
        : [...prev, filterId]
    )
  }

  const filteredFacilities = healthFacilities.filter((facility) => {
    const matchesSearch =
      facility.name.toLowerCase().includes(searchQuery.toLowerCase()) ||
      facility.address.toLowerCase().includes(searchQuery.toLowerCase())
    
    const matchesType = selectedType ? facility.type === selectedType : true
    
    let matchesFilter = true
    if (activeFilter === "24h") {
      matchesFilter = facility.status === "24h"
    } else if (activeFilter === "baratas") {
      matchesFilter = facility.type === "farmacia"
    } else if (activeFilter === "avaliadas") {
      matchesFilter = (facility.rating || 0) >= 4.5
    }

    return matchesSearch && matchesType && matchesFilter
  }).sort((a, b) => {
    if (activeFilter === "proximas") {
      return parseFloat(a.distance || "0") - parseFloat(b.distance || "0")
    }
    if (activeFilter === "avaliadas") {
      return (b.rating || 0) - (a.rating || 0)
    }
    return 0
  })

  // Fullscreen map view
  if (isMapFullscreen) {
    return (
      <div className="fixed inset-0 z-50 bg-background">
        <AngolaMap 
          facilities={filteredFacilities} 
          isFullscreen={true}
          onExitFullscreen={() => setIsMapFullscreen(false)}
        />
      </div>
    )
  }

  return (
    <div className="flex flex-col md:flex-row h-[calc(100vh-4rem)] overflow-hidden -mt-8 md:-mt-0">
      {/* Sidebar List */}
      <section className="w-full md:w-96 bg-background flex flex-col h-full border-r border-border/15 z-20">
        {/* Search Header */}
        <div className="p-4 md:p-6 space-y-4">
          <div className="relative">
            <div className="absolute inset-y-0 left-4 flex items-center pointer-events-none">
              <Search className="w-5 h-5 text-muted-foreground" />
            </div>
            <Input
              type="text"
              placeholder="Procurar farmacia, hospital..."
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              className="w-full pl-12 pr-4 py-4 bg-muted border-none rounded-2xl text-sm"
            />
          </div>
          
          {/* Type Filters */}
          <div className="flex gap-2 overflow-x-auto pb-1 scrollbar-hide">
            {typeFilters.map((type) => {
              const Icon = type.icon
              return (
                <button
                  key={type.id ?? "all"}
                  onClick={() => setSelectedType(type.id)}
                  className={`px-3 py-2 rounded-xl text-xs font-semibold whitespace-nowrap transition-all flex items-center gap-1.5 ${
                    selectedType === type.id
                      ? "bg-primary text-primary-foreground shadow-md"
                      : "bg-muted text-muted-foreground hover:bg-muted/80"
                  }`}
                >
                  {Icon && <Icon className="w-3.5 h-3.5" />}
                  {type.label}
                </button>
              )
            })}
          </div>

          {/* Main Filters + More Button */}
          <div className="flex gap-2 items-center">
            <div className="flex gap-2 overflow-x-auto flex-1 scrollbar-hide">
              {mainFilters.map((filter) => {
                const Icon = filter.icon
                return (
                  <button
                    key={filter.id}
                    onClick={() => setActiveFilter(filter.id)}
                    className={`px-3 py-2 rounded-xl text-xs font-medium whitespace-nowrap transition-all flex items-center gap-1.5 ${
                      activeFilter === filter.id
                        ? "bg-secondary text-foreground border border-primary/20"
                        : "bg-surface-container text-muted-foreground hover:bg-muted"
                    }`}
                  >
                    <Icon className="w-3.5 h-3.5" />
                    {filter.label}
                  </button>
                )
              })}
            </div>

            {/* More Filters Dropdown */}
            <DropdownMenu>
              <DropdownMenuTrigger asChild>
                <Button 
                  variant="outline" 
                  size="sm" 
                  className={`rounded-xl h-9 px-3 gap-1.5 shrink-0 ${
                    extraActiveFilters.length > 0 ? "border-primary bg-primary/5" : ""
                  }`}
                >
                  <SlidersHorizontal className="w-3.5 h-3.5" />
                  <span className="hidden sm:inline">Mais</span>
                  {extraActiveFilters.length > 0 && (
                    <span className="w-5 h-5 rounded-full bg-primary text-primary-foreground text-[10px] flex items-center justify-center font-bold">
                      {extraActiveFilters.length}
                    </span>
                  )}
                </Button>
              </DropdownMenuTrigger>
              <DropdownMenuContent align="end" className="w-56">
                <DropdownMenuLabel>Filtros Adicionais</DropdownMenuLabel>
                <DropdownMenuSeparator />
                {extraFilters.map((filter) => (
                  <DropdownMenuCheckboxItem
                    key={filter.id}
                    checked={extraActiveFilters.includes(filter.id)}
                    onCheckedChange={() => toggleExtraFilter(filter.id)}
                  >
                    {filter.label}
                  </DropdownMenuCheckboxItem>
                ))}
                {extraActiveFilters.length > 0 && (
                  <>
                    <DropdownMenuSeparator />
                    <button 
                      className="w-full px-2 py-1.5 text-xs text-muted-foreground hover:text-foreground text-left flex items-center gap-2"
                      onClick={() => setExtraActiveFilters([])}
                    >
                      <X className="w-3 h-3" />
                      Limpar filtros
                    </button>
                  </>
                )}
              </DropdownMenuContent>
            </DropdownMenu>
          </div>

          {/* Active Extra Filters Pills */}
          {extraActiveFilters.length > 0 && (
            <div className="flex gap-2 flex-wrap">
              {extraActiveFilters.map((filterId) => {
                const filter = extraFilters.find(f => f.id === filterId)
                return (
                  <span 
                    key={filterId}
                    className="inline-flex items-center gap-1 px-2 py-1 bg-primary/10 text-primary text-xs rounded-lg"
                  >
                    <Check className="w-3 h-3" />
                    {filter?.label}
                    <button 
                      onClick={() => toggleExtraFilter(filterId)}
                      className="ml-1 hover:bg-primary/20 rounded p-0.5"
                    >
                      <X className="w-3 h-3" />
                    </button>
                  </span>
                )
              })}
            </div>
          )}
        </div>

        {/* Facilities Feed */}
        <div className="flex-1 overflow-y-auto px-4 md:px-6 space-y-3 pb-24">
          <div className="flex items-center justify-between">
            <h2 className="text-xs font-bold text-muted-foreground uppercase tracking-wider">
              Proximas de si ({filteredFacilities.length})
            </h2>
            {/* Mobile map toggle */}
            <Button
              variant="ghost"
              size="sm"
              className="md:hidden text-xs gap-1.5"
              onClick={() => setIsMapFullscreen(true)}
            >
              <MapPin className="w-3.5 h-3.5" />
              Ver Mapa
            </Button>
          </div>
          
          {filteredFacilities.map((facility) => (
            <HealthFacilityCard key={facility.id} facility={facility} />
          ))}

          {filteredFacilities.length === 0 && (
            <div className="text-center py-8 text-muted-foreground">
              <p>Nenhuma instituicao encontrada</p>
            </div>
          )}
        </div>
      </section>

      {/* Map Section - Hidden on mobile, shown in fullscreen mode */}
      <div className="hidden md:flex flex-1 relative">
        <AngolaMap 
          facilities={filteredFacilities} 
          onEnterFullscreen={() => setIsMapFullscreen(true)}
        />
      </div>
    </div>
  )
}
