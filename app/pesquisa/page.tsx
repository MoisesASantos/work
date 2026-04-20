"use client"

import { useState } from "react"
import { Search, SlidersHorizontal, X, Clock, MapPin, Banknote, Star, Building2, Pill, Stethoscope, Check } from "lucide-react"
import { Input } from "@/components/ui/input"
import { Button } from "@/components/ui/button"
import { HealthFacilityCard, type HealthFacility } from "@/components/health/health-facility-card"
import { MedicineCard, type Medicine } from "@/components/pharmacy/medicine-card"
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
    name: "Farmácia Welwitschia",
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
    address: "Maianga, Av. Revolução de Outubro",
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
    name: "Centro de Saúde do Cazenga",
    type: "posto",
    address: "Cazenga, Rua Principal",
    rating: 4.3,
    reviews: "156",
    distance: "4.0 km",
    status: "open",
  },
  {
    id: "clinica-sagrada",
    name: "Clínica Sagrada Esperança",
    type: "hospital",
    address: "Talatona, Zona Económica",
    rating: 4.9,
    reviews: "1.2k",
    distance: "5.2 km",
    status: "24h",
    featured: true,
  },
  {
    id: "farmacia-central",
    name: "Farmácia Central",
    type: "farmacia",
    address: "Ingombota, Rua Rainha Ginga",
    rating: 4.5,
    reviews: "89",
    distance: "1.8 km",
    status: "closing-soon",
  },
  {
    id: "posto-viana",
    name: "Posto Médico de Viana",
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
  { id: "proximas", label: "Mais Próximas", icon: MapPin },
  { id: "baratas", label: "Mais Baratas", icon: Banknote },
  { id: "avaliadas", label: "Melhor Avaliadas", icon: Star },
]

// Additional filters that were in dropdown
const extraFilters = [
  { id: "abertas", label: "Abertas Agora" },
  { id: "estacionamento", label: "Com Estacionamento" },
  { id: "acessibilidade", label: "Acessível" },
  { id: "plantao", label: "Em Plantão" },
]

// Combined filters in dropdown
const allExtraFilters = [
  ...mainFilters,
  ...extraFilters
]

const typeFilters = [
  { id: null, label: "Todos", icon: null },
  { id: "farmacia", label: "Farmácias", icon: Pill },
  { id: "hospital", label: "Hospitais", icon: Building2 },
  { id: "posto", label: "Postos Médicos", icon: Stethoscope },
]

// Mock medicines database
const mockMedicines: (Medicine & { pharmacyId: string, pharmacyName: string, distance: string, status: string })[] = [
  {
    id: "med-1",
    name: "Paracetamol 500mg",
    description: "Analgésico e antipirético.",
    price: 1500,
    image: "https://images.unsplash.com/photo-1584308666744-24d5c474f2ae?w=400&q=80",
    inStock: true,
    pharmacyId: "welwitschia",
    pharmacyName: "Farmácia Welwitschia",
    distance: "1.2 km",
    status: "open",
  },
  {
    id: "med-2",
    name: "Ibuprofeno 400mg",
    description: "Anti-inflamatório não esteroide.",
    price: 2200,
    image: "https://images.unsplash.com/photo-1628771065518-0d82f1938462?w=400&q=80",
    inStock: true,
    pharmacyId: "maianga",
    pharmacyName: "Apothecary Maianga",
    distance: "2.5 km",
    status: "24h",
  },
  {
    id: "med-3",
    name: "Amoxicilina 500mg",
    description: "Antibiótico.",
    price: 3500,
    image: "https://images.unsplash.com/photo-1471864190281-a93a3070b6de?w=400&q=80",
    inStock: true,
    requiresPrescription: true,
    pharmacyId: "maianga",
    pharmacyName: "Apothecary Maianga",
    distance: "2.5 km",
    status: "24h",
  },
  {
    id: "med-4",
    name: "Vitamina C 1g",
    description: "Suplemento vitamínico.",
    price: 1800,
    image: "https://images.unsplash.com/photo-1550572017-edb3f5728a33?w=400&q=80",
    inStock: true,
    pharmacyId: "farmacia-central",
    pharmacyName: "Farmácia Central",
    distance: "1.8 km",
    status: "closing-soon",
  },
]

export default function ExplorePage() {
  const [searchQuery, setSearchQuery] = useState("")
  const [selectedType, setSelectedType] = useState<string | null>(null)
  const [extraActiveFilters, setExtraActiveFilters] = useState<string[]>(["proximas"])
  const [isMapFullscreen, setIsMapFullscreen] = useState(false)

  const toggleExtraFilter = (filterId: string) => {
    setExtraActiveFilters(prev => 
      prev.includes(filterId) 
        ? prev.filter(f => f !== filterId)
        : [...prev, filterId]
    )
  }

  // Handle unified search: decide if it's a facility match or a medicine match
  const searchStr = searchQuery.toLowerCase().trim()
  
  // Find matched medicines from the database (simulated)
  const matchedMedicines = searchStr 
    ? mockMedicines.filter((med) => med.name.toLowerCase().includes(searchStr))
    : []

  const isLookingForMedicine = matchedMedicines.length > 0

  type SearchResult = 
    | { type: "facility"; facility: HealthFacility }
    | { type: "medicineList"; facility: HealthFacility; medicine: typeof mockMedicines[0] }

  let results: SearchResult[] = []

  if (isLookingForMedicine) {
    // Return the pharmacies that have the searched medicine
    matchedMedicines.forEach(med => {
      const facility = healthFacilities.find(f => f.id === med.pharmacyId)
      if (!facility) return
      
      // Apply filters for facility holding the medicine
      if (selectedType && facility.type !== selectedType) return
      if (extraActiveFilters.includes("24h") && facility.status !== "24h") return
      if (extraActiveFilters.includes("avaliadas") && (facility.rating || 0) < 4.5) return
      
      results.push({ type: "medicineList", facility, medicine: med })
    })
  } else {
    // Normal facility search
    let matchingFacilities = healthFacilities
    if (searchStr) {
      matchingFacilities = matchingFacilities.filter((facility) => 
        facility.name.toLowerCase().includes(searchStr) ||
        facility.address.toLowerCase().includes(searchStr)
      )
    }
    
    matchingFacilities.forEach((facility) => {
      if (selectedType && facility.type !== selectedType) return
      if (extraActiveFilters.includes("24h") && facility.status !== "24h") return
      if (extraActiveFilters.includes("baratas") && facility.type !== "farmacia") return
      if (extraActiveFilters.includes("avaliadas") && (facility.rating || 0) < 4.5) return

      results.push({ type: "facility", facility })
    })
  }

  // Sort results according to active filter
  results = results.sort((a, b) => {
    if (extraActiveFilters.includes("baratas") && isLookingForMedicine) {
      // Sort by medicine price if searching for medicine & "baratas" is active
      const medA = a.type === "medicineList" ? a.medicine.price : 0
      const medB = b.type === "medicineList" ? b.medicine.price : 0
      return medA - medB
    }
    if (extraActiveFilters.includes("proximas")) {
      const distA = parseFloat(a.facility.distance || "0")
      const distB = parseFloat(b.facility.distance || "0")
      return distA - distB
    }
    if (extraActiveFilters.includes("avaliadas")) {
      return (b.facility.rating || 0) - (a.facility.rating || 0)
    }
    return 0
  })

  // Fullscreen map view
  if (isMapFullscreen) {
    return (
      <div className="fixed inset-0 z-50 bg-background">
        <AngolaMap 
          facilities={results.map(r => r.facility).filter((f, i, self) => i === self.findIndex(t => t.id === f.id))} 
          isFullscreen={true}
          onExitFullscreen={() => setIsMapFullscreen(false)}
        />
      </div>
    )
  }

  return (
    <div className="flex flex-col md:flex-row h-[calc(100vh-4rem)] overflow-hidden">
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
              placeholder="Procurar farmácia, hospital ou medicamento..."
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              className="w-full pl-12 pr-4 py-4 bg-muted border-none rounded-2xl text-sm"
            />
          </div>
          
          {/* Type Filters + More Button */}
          <div className="flex gap-2 items-center">
            <div className="flex gap-2 overflow-x-auto flex-1 scrollbar-hide">
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
                {allExtraFilters.map((filter) => (
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
                const filter = allExtraFilters.find(f => f.id === filterId)
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
          {/* Unified Search Results Feed */}
        <div className="flex-1 overflow-y-auto px-4 md:px-6 space-y-3 pb-24">
          <div className="flex items-center justify-between">
            <h2 className="text-xs font-bold text-muted-foreground uppercase tracking-wider">
              {isLookingForMedicine ? "Farmácias com o medicamento" : "Próximas de si"} ({results.length})
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
          
          {results.map((result, idx) => {
            if (result.type === "facility") {
              return <HealthFacilityCard key={`facility-${result.facility.id}-${idx}`} facility={result.facility} />
            }

            // Render medicine matched inside pharmacy context
            return (
              <div key={`med-${result.medicine.id}-${idx}`} className="relative bg-card rounded-2xl shadow-sm border border-border/5 group overflow-hidden">
                <HealthFacilityCard facility={result.facility} className="shadow-none rounded-none border-b border-border/10 pb-4 mb-0" />
                <div className="px-5 py-3 bg-muted/30">
                  <div className="flex justify-between items-center">
                    <div className="flex items-center gap-3">
                      <img 
                        src={result.medicine.image} 
                        alt={result.medicine.name} 
                        className="w-8 h-8 object-cover rounded-lg mix-blend-multiply opacity-80" 
                      />
                      <div>
                        <p className="font-bold text-sm text-foreground">{result.medicine.name}</p>
                        <p className="text-[10px] text-muted-foreground">
                          {result.medicine.inStock ? "Produto em Estoque" : "Esgotado"}
                        </p>
                      </div>
                    </div>
                    <div className="text-right">
                      <span suppressHydrationWarning className="block font-black text-primary text-sm">
                        {result.medicine.price.toLocaleString()} <span className="text-[10px] font-medium">Kz</span>
                      </span>
                    </div>
                  </div>
                </div>
              </div>
            )
          })}

          {results.length === 0 && (
            <div className="text-center py-8 text-muted-foreground">
              <p>Nenhuma correspondência encontrada</p>
            </div>
          )}
        </div>
      </section>

      {/* Map Section - Hidden on mobile, shown in fullscreen mode */}
      <div className="hidden md:flex flex-1 relative">
        <AngolaMap 
          facilities={results.map(r => r.facility).filter((f, i, self) => i === self.findIndex(t => t.id === f.id))} 
          onEnterFullscreen={() => setIsMapFullscreen(true)}
        />
      </div>
    </div>
  )
}
          </div>
        </header>

        {/* Results */}
        <div className="space-y-6">
          {searchResults.map((result) => (
            <Link
              key={result.id}
              href={`/farmacias/${result.id}`}
              className={`block bg-card p-5 rounded-xl transition-all hover:shadow-lg group ${
                !result.inStock ? "opacity-60 border border-dashed border-border" : ""
              }`}
            >
              <div className="flex justify-between items-start mb-4">
                <div className="flex gap-4">
                  <div className="w-14 h-14 rounded-lg bg-muted flex items-center justify-center overflow-hidden">
                    <img
                      src={result.logo}
                      alt={result.pharmacyName}
                      className={`w-full h-full object-cover ${!result.inStock ? "grayscale" : ""}`}
                    />
                  </div>
                  <div>
                    <h3 className="text-lg font-bold text-primary group-hover:text-primary/80 transition-colors">
                      {result.pharmacyName}
                    </h3>
                    <div className="flex items-center gap-1 text-sm text-muted-foreground mt-1">
                      <MapPin className="w-4 h-4" />
                      <span>{result.address}</span>
                    </div>
                  </div>
                </div>
                <div className="text-right">
                  {result.inStock ? (
                    <>
                      <div suppressHydrationWarning className="text-2xl font-extrabold text-primary">
                        {result.price.toLocaleString()} <span className="text-xs font-medium text-muted-foreground">Kz</span>
                      </div>
                      <span className="text-[10px] uppercase tracking-wider font-bold text-tertiary bg-tertiary-fixed px-2 py-0.5 rounded">
                        Em Stock
                      </span>
                    </>
                  ) : (
                    <>
                      <div className="text-2xl font-extrabold text-muted-foreground">---</div>
                      <span className="text-[10px] uppercase tracking-wider font-bold text-destructive bg-destructive/10 px-2 py-0.5 rounded">
                        Esgotado
                      </span>
                    </>
                  )}
                </div>
              </div>

              <div className="flex items-center justify-between pt-4 border-t border-border/15">
                {result.inStock ? (
                  <>
                    <div className="flex gap-4 text-xs font-medium text-muted-foreground">
                      <span className="flex items-center gap-1">
                        <Clock className="w-3.5 h-3.5" /> {result.hours}
                      </span>
                      <span className="flex items-center gap-1">
                        <Car className="w-3.5 h-3.5" /> {result.distance}
                      </span>
                    </div>
                    <Button size="sm" className="rounded-lg font-bold shadow-sm">
                      Reservar
                    </Button>
                  </>
                ) : (
                  <>
                    <p className="text-xs italic text-muted-foreground">{result.restockTime}</p>
                    <button className="text-primary text-sm font-bold hover:underline">Ver Similares</button>
                  </>
                )}
              </div>
            </Link>
          ))}
        </div>
      </section>

      {/* Map Section */}
      <section className="hidden md:block flex-1 sticky top-16 h-[calc(100vh-64px)] overflow-hidden bg-muted">
        <div className="relative h-full w-full">
          <img
            src="https://images.unsplash.com/photo-1524661135-423995f22d0b?w=1200&h=800&fit=crop"
            alt="Mapa de Luanda"
            className="w-full h-full object-cover"
          />

          {/* Price Markers */}
          <div className="absolute top-[30%] left-[40%]">
            <div className="flex flex-col items-center">
              <div className="bg-primary text-primary-foreground px-3 py-1 rounded-full text-[10px] font-bold shadow-lg mb-1">
                1.250 Kz
              </div>
              <MapPin className="w-8 h-8 text-primary fill-primary" />
            </div>
          </div>
          <div className="absolute top-[65%] left-[55%]">
            <div className="flex flex-col items-center">
              <div className="bg-primary text-primary-foreground px-3 py-1 rounded-full text-[10px] font-bold shadow-lg mb-1">
                1.400 Kz
              </div>
              <MapPin className="w-8 h-8 text-primary fill-primary" />
            </div>
          </div>

          {/* Map Controls */}
          <div className="absolute top-6 right-6 flex flex-col gap-2">
            <button className="bg-white/80 backdrop-blur-xl p-2 rounded-lg text-primary shadow-sm hover:bg-white transition-colors">
              <Plus className="w-5 h-5" />
            </button>
            <button className="bg-white/80 backdrop-blur-xl p-2 rounded-lg text-primary shadow-sm hover:bg-white transition-colors">
              <Minus className="w-5 h-5" />
            </button>
          </div>

          <div className="absolute bottom-10 left-1/2 -translate-x-1/2 bg-white/80 backdrop-blur-xl px-6 py-3 rounded-2xl flex items-center gap-4 shadow-xl border border-white/20">
            <LocateFixed className="w-5 h-5 text-primary" />
            <span className="text-sm font-medium text-primary whitespace-nowrap">Pesquisar nesta area</span>
          </div>
        </div>
      </section>
    </div>
  )
}
