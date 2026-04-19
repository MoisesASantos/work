"use client"

import { useState, useRef } from "react"
import { Upload, Camera, Eye, BadgeCheck, Plus, Minus, ArrowRight, Sparkles, Pill, ShieldCheck } from "lucide-react"
import { Button } from "@/components/ui/button"
import { cn } from "@/lib/utils"

interface IdentifiedMedicine {
  id: string
  name: string
  description: string
  confidence: number
  price: number
  quantity: number
}

const mockIdentifiedMedicines: IdentifiedMedicine[] = [
  {
    id: "amoxicilina",
    name: "Amoxicilina 500mg",
    description: "Cápsulas - Uso contínuo (7 dias)",
    confidence: 98,
    price: 2450,
    quantity: 1,
  },
  {
    id: "paracetamol",
    name: "Paracetamol 1g",
    description: "Comprimidos - SOS (Dor/Febre)",
    confidence: 95,
    price: 1200,
    quantity: 2,
  },
]

export default function ReceitasPage() {
  const [uploadedImage, setUploadedImage] = useState<string | null>(null)
  const [isAnalyzing, setIsAnalyzing] = useState(false)
  const [identifiedMedicines, setIdentifiedMedicines] = useState<IdentifiedMedicine[]>([])
  const fileInputRef = useRef<HTMLInputElement>(null)

  const handleFileUpload = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0]
    if (file) {
      const reader = new FileReader()
      reader.onload = (e) => {
        setUploadedImage(e.target?.result as string)
        simulateAnalysis()
      }
      reader.readAsDataURL(file)
    }
  }

  const simulateAnalysis = () => {
    setIsAnalyzing(true)
    setTimeout(() => {
      setIdentifiedMedicines(mockIdentifiedMedicines)
      setIsAnalyzing(false)
    }, 2000)
  }

  const updateQuantity = (id: string, delta: number) => {
    setIdentifiedMedicines((prev) =>
      prev.map((med) =>
        med.id === id ? { ...med, quantity: Math.max(1, med.quantity + delta) } : med
      )
    )
  }

  const totalPrice = identifiedMedicines.reduce(
    (sum, med) => sum + med.price * med.quantity,
    0
  )

  return (
    <div className="px-6 md:px-12 max-w-7xl mx-auto py-8">
      {/* Hero Section */}
      <section className="mb-12">
        <div className="max-w-2xl">
          <h1 className="text-4xl md:text-5xl font-extrabold text-primary tracking-tight mb-4 leading-tight font-serif">
            Digitalize a sua Receita.
          </h1>
          <p className="text-lg text-muted-foreground leading-relaxed">
            Carregue a foto da sua prescrição médica. A nossa Inteligência Artificial identificará automaticamente os medicamentos e verificará o stock nas farmácias mais próximas de Luanda.
          </p>
        </div>
      </section>

      {/* Bento Grid Layout */}
      <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 items-start">
        {/* Column 1: Upload Zone */}
        <div className="lg:col-span-7 space-y-6">
          {/* Upload Card */}
          <div
            onClick={() => fileInputRef.current?.click()}
            className="relative overflow-hidden rounded-[32px] bg-card border-2 border-dashed border-primary/20 shadow-sm p-8 h-full flex flex-col justify-center min-h-[400px] cursor-pointer hover:border-primary/40 transition-colors"
          >
            <div className="absolute inset-0 bg-gradient-to-br from-primary/5 to-transparent pointer-events-none" />
            <input
              ref={fileInputRef}
              type="file"
              accept="image/*,.pdf"
              onChange={handleFileUpload}
              className="hidden"
            />
            <div className="relative z-10 text-center space-y-6">
              <div className="w-24 h-24 bg-primary/10 rounded-full flex items-center justify-center mx-auto mb-4">
                <Upload className="w-12 h-12 text-primary" />
              </div>
              <div>
                <h3 className="text-2xl font-bold text-primary mb-2">Arraste a foto da receita</h3>
                <p className="text-muted-foreground max-w-sm mx-auto">
                  Suporta formatos JPG, PNG ou PDF de alta qualidade para melhor reconhecimento.
                </p>
              </div>
              <Button size="lg" className="px-8 rounded-full shadow-lg">
                <Camera className="w-5 h-5 mr-2" />
                Selecionar Arquivo
              </Button>
              <div className="pt-4 text-xs text-muted-foreground font-medium tracking-widest uppercase flex items-center justify-center gap-2">
                <ShieldCheck className="w-4 h-4" />
                Seguro & Privado - Encriptação de 256 bits
              </div>
            </div>
          </div>

          {/* Preview Card */}
          {(uploadedImage || isAnalyzing) && (
            <div className="bg-muted rounded-[24px] p-6 relative group overflow-hidden">
              <div className="flex items-center justify-between mb-6">
                <h4 className="font-bold text-primary flex items-center gap-2">
                  <Eye className="w-5 h-5" />
                  Visualização da Receita
                </h4>
                {!isAnalyzing && identifiedMedicines.length > 0 && (
                  <span className="px-3 py-1 bg-tertiary-fixed text-on-tertiary-fixed text-[11px] font-bold rounded-full uppercase tracking-tighter">
                    Analisado por IA
                  </span>
                )}
              </div>
              <div className="aspect-[4/3] rounded-xl overflow-hidden shadow-sm relative bg-white">
                {uploadedImage ? (
                  <img
                    src={uploadedImage}
                    alt="Receita carregada"
                    className={cn(
                      "w-full h-full object-contain",
                      isAnalyzing && "opacity-50"
                    )}
                  />
                ) : (
                  <div className="w-full h-full flex items-center justify-center bg-muted">
                    <p className="text-muted-foreground">Nenhuma imagem carregada</p>
                  </div>
                )}

                {isAnalyzing && (
                  <div className="absolute inset-0 flex items-center justify-center bg-white/80">
                    <div className="flex flex-col items-center gap-4">
                      <div className="w-12 h-12 border-4 border-primary border-t-transparent rounded-full animate-spin" />
                      <p className="text-sm font-medium text-primary">Analisando receita...</p>
                    </div>
                  </div>
                )}

                {/* Detection Overlays */}
                {!isAnalyzing && identifiedMedicines.length > 0 && (
                  <>
                    <div className="absolute top-[20%] left-[15%] w-[40%] h-[10%] border-2 border-tertiary rounded-lg bg-tertiary/10 backdrop-blur-[2px]">
                      <span className="text-[10px] font-bold text-white bg-tertiary px-1 rounded absolute -top-4 left-0">
                        AMOXICILINA 500MG
                      </span>
                    </div>
                    <div className="absolute top-[45%] left-[15%] w-[35%] h-[8%] border-2 border-tertiary rounded-lg bg-tertiary/10 backdrop-blur-[2px]">
                      <span className="text-[10px] font-bold text-white bg-tertiary px-1 rounded absolute -top-4 left-0">
                        PARACETAMOL
                      </span>
                    </div>
                  </>
                )}
              </div>
            </div>
          )}
        </div>

        {/* Column 2: Results */}
        <div className="lg:col-span-5 space-y-6">
          <div className="bg-card rounded-[32px] p-8 shadow-sm border border-border/10">
            <div className="mb-8">
              <h3 className="text-2xl font-bold text-primary font-serif">Medicamentos Identificados</h3>
              <p className="text-sm text-muted-foreground mt-1">
                {identifiedMedicines.length > 0
                  ? "Confirmamos os itens abaixo com base na imagem."
                  : "Carregue uma receita para comecar a analise."}
              </p>
            </div>

            {/* Identified Items */}
            <div className="space-y-4">
              {identifiedMedicines.map((medicine) => (
                <div
                  key={medicine.id}
                  className="p-4 bg-muted rounded-xl border border-transparent hover:border-primary/20 transition-all flex items-start gap-4"
                >
                  <div className="w-12 h-12 bg-white rounded-lg flex items-center justify-center flex-shrink-0 shadow-sm">
                    <Pill className="w-6 h-6 text-primary" />
                  </div>
                  <div className="flex-1">
                    <div className="flex justify-between items-start">
                      <h5 className="font-bold text-foreground">{medicine.name}</h5>
                      <span className="text-xs font-bold text-tertiary flex items-center gap-1">
                        <BadgeCheck className="w-4 h-4" />
                        {medicine.confidence}% Confianca
                      </span>
                    </div>
                    <p className="text-xs text-muted-foreground mt-1">{medicine.description}</p>
                    <div className="mt-3 flex items-center justify-between">
                      <span suppressHydrationWarning className="text-primary font-bold text-lg">
                        {medicine.price.toLocaleString()} <span className="text-xs">Kz</span>
                      </span>
                      <div className="flex items-center gap-2">
                        <button
                          onClick={() => updateQuantity(medicine.id, -1)}
                          className="w-8 h-8 rounded-lg bg-white flex items-center justify-center text-primary border border-border/30 hover:bg-muted transition-colors"
                        >
                          <Minus className="w-4 h-4" />
                        </button>
                        <span className="font-bold text-sm w-6 text-center">{medicine.quantity}</span>
                        <button
                          onClick={() => updateQuantity(medicine.id, 1)}
                          className="w-8 h-8 rounded-lg bg-white flex items-center justify-center text-primary border border-border/30 hover:bg-muted transition-colors"
                        >
                          <Plus className="w-4 h-4" />
                        </button>
                      </div>
                    </div>
                  </div>
                </div>
              ))}

              {/* Manual Add Button */}
              <button className="w-full py-4 border-2 border-dashed border-border/40 rounded-xl text-muted-foreground font-semibold flex items-center justify-center gap-2 hover:bg-muted transition-colors">
                <Plus className="w-5 h-5" />
                Adicionar medicamento manualmente
              </button>
            </div>

            {/* Summary */}
            {identifiedMedicines.length > 0 && (
              <div className="mt-10 pt-8 border-t border-border/20">
                <div className="flex justify-between mb-2">
                  <span className="text-muted-foreground">
                    Subtotal ({identifiedMedicines.reduce((sum, m) => sum + m.quantity, 0)} Itens)
                  </span>
                  <span suppressHydrationWarning className="font-bold">{totalPrice.toLocaleString()} Kz</span>
                </div>
                <div className="flex justify-between mb-6">
                  <span className="text-muted-foreground">Taxa de Servico</span>
                  <span className="text-tertiary font-bold">Gratis</span>
                </div>
                <div className="flex justify-between items-end mb-8">
                  <span className="text-primary font-bold">Total Estimado</span>
                  <span suppressHydrationWarning className="text-primary text-3xl font-black">{totalPrice.toLocaleString()} Kz</span>
                </div>
                <Button size="lg" className="w-full py-6 rounded-2xl font-extrabold text-lg shadow-xl">
                  Prosseguir para Encomenda
                  <ArrowRight className="w-5 h-5 ml-2" />
                </Button>
              </div>
            )}
          </div>

          {/* Info Card */}
          <div className="bg-primary text-primary-foreground rounded-[24px] p-6 relative overflow-hidden">
            <div className="absolute top-0 right-0 w-32 h-32 bg-white/5 rounded-full -mr-16 -mt-16 blur-2xl" />
            <div className="relative z-10">
              <h5 className="font-bold mb-2 flex items-center gap-2">
                <Sparkles className="w-5 h-5" />
                Dica de Especialista
              </h5>
              <p className="text-sm opacity-90 leading-relaxed">
                A nossa IA pode sugerir alternativas genericas aprovadas pela ARMED para poupar ate 40% no valor total.
              </p>
            </div>
          </div>
        </div>
      </div>
    </div>
  )
}
