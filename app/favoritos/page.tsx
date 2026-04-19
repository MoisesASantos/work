"use client"

import { Heart, MapPin, Star, Trash2 } from "lucide-react"
import { Button } from "@/components/ui/button"
import Link from "next/link"

const favoritePharmacies = [
  {
    id: "maianga",
    name: "Apothecary Maianga",
    address: "Maianga, Av. Revolução de Outubro",
    rating: 4.9,
    reviews: "340+",
    status: "24h",
  },
  {
    id: "welwitschia",
    name: "Farmácia Welwitschia",
    address: "Talatona, Rua do MAT",
    rating: 4.8,
    reviews: "120+",
    status: "Aberto",
  },
]

const favoriteMedicines = [
  {
    id: "paracetamol",
    name: "Paracetamol 500mg",
    description: "Caixa de 20 comprimidos",
    price: 1250,
  },
  {
    id: "vitamina-c",
    name: "Vitamina C 1g",
    description: "Tubo 10 pastilhas eferv.",
    price: 2400,
  },
]

export default function FavoritosPage() {
  return (
    <div className="px-6 md:px-12 max-w-6xl mx-auto py-8">
      <h1 className="text-3xl font-extrabold text-primary mb-2 font-serif">Meus Favoritos</h1>
      <p className="text-muted-foreground mb-8">Aceda rapidamente às suas farmácias e medicamentos preferidos.</p>

      {/* Favorite Pharmacies */}
      <section className="mb-12">
        <h2 className="text-lg font-bold text-foreground mb-4 flex items-center gap-2">
          <Heart className="w-5 h-5 text-destructive fill-destructive" />
          Instituições de Saúde Favoritas
        </h2>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
          {favoritePharmacies.map((pharmacy) => (
            <Link
              key={pharmacy.id}
              href={`/instituicao/${pharmacy.id}`}
              className="bg-card p-5 rounded-2xl shadow-sm hover:shadow-md transition-shadow group"
            >
              <div className="flex justify-between items-start mb-3">
                <div>
                  <h3 className="font-bold text-primary group-hover:text-primary/80 transition-colors">
                    {pharmacy.name}
                  </h3>
                  <p className="text-xs text-muted-foreground flex items-center gap-1 mt-1">
                    <MapPin className="w-3.5 h-3.5" />
                    {pharmacy.address}
                  </p>
                </div>
                <span className="bg-tertiary-fixed text-on-tertiary-fixed px-2 py-1 rounded text-[10px] font-bold uppercase">
                  {pharmacy.status}
                </span>
              </div>
              <div className="flex items-center justify-between mt-4">
                <div className="flex items-center gap-1">
                  <Star className="w-4 h-4 text-tertiary fill-tertiary" />
                  <span className="text-xs font-bold">{pharmacy.rating}</span>
                  <span className="text-[10px] text-muted-foreground">({pharmacy.reviews})</span>
                </div>
                <button className="text-destructive hover:text-destructive/80 transition-colors">
                  <Trash2 className="w-4 h-4" />
                </button>
              </div>
            </Link>
          ))}
        </div>
      </section>

      {/* Favorite Medicines */}
      <section>
        <h2 className="text-lg font-bold text-foreground mb-4 flex items-center gap-2">
          <Heart className="w-5 h-5 text-destructive fill-destructive" />
          Medicamentos Favoritos
        </h2>
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
          {favoriteMedicines.map((medicine) => (
            <div
              key={medicine.id}
              className="bg-card p-5 rounded-2xl shadow-sm hover:shadow-md transition-shadow"
            >
              <div className="flex justify-between items-start">
                <div>
                  <h3 className="font-bold text-foreground">{medicine.name}</h3>
                  <p className="text-xs text-muted-foreground mt-1">{medicine.description}</p>
                </div>
                <button className="text-destructive hover:text-destructive/80 transition-colors">
                  <Trash2 className="w-4 h-4" />
                </button>
              </div>
              <div className="flex items-center justify-between mt-4">
                <p suppressHydrationWarning className="text-lg font-black text-primary">
                  {medicine.price.toLocaleString()} <span className="text-xs font-medium">Kz</span>
                </p>
                <Button size="sm" className="rounded-lg">
                  Encontrar
                </Button>
              </div>
            </div>
          ))}
        </div>
      </section>

      {favoritePharmacies.length === 0 && favoriteMedicines.length === 0 && (
        <div className="text-center py-16">
          <Heart className="w-16 h-16 text-muted-foreground mx-auto mb-4" />
          <h3 className="text-xl font-bold text-foreground mb-2">Nenhum favorito ainda</h3>
          <p className="text-muted-foreground mb-6">
            Comece a adicionar instituições de saúde e medicamentos aos seus favoritos.
          </p>
          <Button asChild>
            <Link href="/">Explorar</Link>
          </Button>
        </div>
      )}
    </div>
  )
}
