"use client"

import { useState } from "react"
import { Search, MapPin, Clock, Car, DollarSign, LocateFixed, Plus, Minus } from "lucide-react"
import { Input } from "@/components/ui/input"
import { Button } from "@/components/ui/button"
import Link from "next/link"

interface SearchResult {
  id: string
  pharmacyName: string
  address: string
  price: number
  inStock: boolean
  hours: string
  distance: string
  restockTime?: string
  logo: string
}

const searchResults: SearchResult[] = [
  {
    id: "prenda",
    pharmacyName: "Farmacia Prenda Express",
    address: "Rua da Prenda, Bloco 4, Luanda",
    price: 1250,
    inStock: true,
    hours: "Aberto 24h",
    distance: "1.2 km",
    logo: "https://images.unsplash.com/photo-1576602976047-174e57a47881?w=100&h=100&fit=crop",
  },
  {
    id: "angofarma",
    pharmacyName: "AngoFarma Talatona",
    address: "Via AL 15, Condominio Dolce Vita",
    price: 1400,
    inStock: true,
    hours: "Fecha as 21:00",
    distance: "4.8 km",
    logo: "https://images.unsplash.com/photo-1587854692152-cbe660dbde88?w=100&h=100&fit=crop",
  },
  {
    id: "central",
    pharmacyName: "Farmacia Central Luanda",
    address: "Largo do Kinaxixi",
    price: 0,
    inStock: false,
    hours: "Aberto",
    distance: "2.1 km",
    restockTime: "Reposicao prevista em 48h",
    logo: "https://images.unsplash.com/photo-1631549916768-4119b2e5f926?w=100&h=100&fit=crop",
  },
]

const filters = [
  { label: "Mais Barato", icon: DollarSign, active: true },
  { label: "Mais Proximo", icon: MapPin, active: false },
  { label: "Em Stock", icon: Clock, active: false },
]

export default function SearchResultsPage() {
  const [searchQuery, setSearchQuery] = useState("Paracetamol")

  return (
    <div className="flex flex-col md:flex-row min-h-[calc(100vh-4rem)]">
      {/* Results List */}
      <section className="w-full md:w-[600px] lg:w-[700px] p-6 overflow-y-auto">
        {/* Search Bar */}
        <div className="mb-6 relative">
          <div className="absolute inset-y-0 left-4 flex items-center pointer-events-none">
            <Search className="w-5 h-5 text-muted-foreground" />
          </div>
          <Input
            type="text"
            value={searchQuery}
            onChange={(e) => setSearchQuery(e.target.value)}
            placeholder="Pesquisar medicamentos..."
            className="w-full pl-12 pr-4 py-4 bg-muted border-none rounded-2xl"
          />
        </div>

        <header className="mb-8">
          <h1 className="text-3xl font-extrabold text-primary mb-2 font-serif">{searchQuery}</h1>
          <p className="text-muted-foreground text-sm">{searchResults.length} resultados encontrados em Luanda</p>

          {/* Filter Chips */}
          <div className="flex gap-3 mt-6">
            {filters.map((filter) => (
              <button
                key={filter.label}
                className={`flex items-center gap-2 px-5 py-2 rounded-full text-sm font-medium transition-all ${
                  filter.active
                    ? "bg-secondary text-secondary-foreground"
                    : "bg-muted text-muted-foreground hover:bg-muted/80"
                }`}
              >
                <filter.icon className="w-4 h-4" />
                {filter.label}
              </button>
            ))}
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
